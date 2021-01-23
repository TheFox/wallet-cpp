
#include <fstream> // ofstream
#include <string>
#include <iterator> // back_inserter
#include <algorithm> // transform
#include <cstdlib> // system

#include "debug.hpp"
#include "config.hpp"
#include "components.hpp"
#include "year_html.hpp"
#include "month_html.hpp"
#include "class/epic.hpp"
#include "class/mustache/year_mustache.hpp"
#ifdef WALLETCPP_GNUPLOT_SUPPORT
#include "class/mustache/year_gnuplot.hpp"
#endif

namespace Wallet::Html
{
  YearHtml::YearHtml(fs::path _basePath, fs::path _tmpPath, Container::YearEntryContainer _container) :
      BaseHtml{std::move(_basePath), std::move(_tmpPath), fs::path{"index.html"},
          "Year " + std::to_string(_container.year)},
      container(std::move(_container))
  {
    //DLog("-> YearHtml::YearHtml('%s', '%s')\n", this->basePath.c_str(), this->getFileName().c_str());
  }

  void YearHtml::generate() const
  {
    //DLog("-> YearHtml::generate() -> %d\n", this->container.year);
    const auto yearStr = std::to_string(this->container.year);
    this->log("[year_html] generate: " + yearStr);

    if (!fs::exists(WALLETCPP_YEAR_VIEW_PATH)) {
      DLog("ERROR: Year template file does not exists: '%s'\n", WALLETCPP_YEAR_VIEW_PATH);
      throw std::string{"Year template file does not exists: "} + WALLETCPP_YEAR_VIEW_PATH;
    }

    // Categories Iterators
    const auto _categories_begin = this->container.categories.cbegin();
    const auto _categories_end = this->container.categories.cend();

    // Category Names
    Container::UnsortedCategories categories{};

    // https://thispointer.com/how-to-copy-all-values-from-a-map-to-a-vector-in-c/
    std::transform(_categories_begin, _categories_end, std::back_inserter(categories), [](const auto& pair) {
      return pair.first;
    });

    // Epic Iterators
    const auto _epics_begin = this->container.epics.cbegin(); // Epic Iterator Begin
    const auto _epics_end = this->container.epics.cend();   // Epic Iterator End

    // Epics
    Container::UnsortedEpicPtrs epicPtrs{};

    // Transform Epics Node to Epics Map (Epics type).
    for (const auto& nodePair : this->container.epics) {
      const auto& epicContainer = nodePair.second;

      //DLog("-> YearHtml::generate() -> transform epic: '%s' -> '%s'\n", nodePair.first.c_str(), (*epicContainer.epicPtr).handle.c_str());

      epicPtrs[nodePair.first] = epicContainer.epicPtr;
    }
    DLog("-> YearHtml::generate() -> epics: %lu\n", epicPtrs.size());

    // Table Body
    mstch::array entries{};

    for (const auto& monthPair : this->container.months) {
      // Month HTML file.
      const MonthHtml monthHtml{this->basePath, monthPair, epicPtrs};
      monthHtml.logLevel = this->logLevel;
      monthHtml.generate();

      // Month Categories
      // Match common categories to month categories.
      mstch::array monthCategories{};
      std::transform(_categories_begin, _categories_end, std::back_inserter(monthCategories),
          [&monthPair](const auto& categoryPair) {
            std::string balance{"&nbsp;"};
            std::string balanceClass{};

            try {
              // Search by key (Name).
              const auto& category = monthPair.second.categories.at(categoryPair.first);
              //DLog("-> YearHtml::generate() category found: '%s'\n", categoryPair.first.c_str());

              balance = category.getBalanceStr();
              balanceClass = category.getBalanceHtmlClass();
            } catch (const std::out_of_range& exception) {
              //DLog("-> YearHtml::generate() nothing found for category: '%s'\n", categoryPair.first.c_str());
            }

            return mstch::map{
                {"balance",       std::move(balance)},
                {"balance_class", std::move(balanceClass)},
            };
          });

      // Month Epics
      // Match common epics to month epics.
      mstch::array monthEpics{};
      std::transform(_epics_begin, _epics_end, std::back_inserter(monthEpics), [&monthPair](const auto& pair) {
        // DLog("-> month epic: '%s'\n", pair.first.c_str());

        try {
          // Search by key (Name).
          DLog("-> search epic: '%s'\n", pair.first.c_str());
          const auto& epicContainer = monthPair.second.epics.at(pair.first);

          const auto& epicPtr = epicContainer.epicPtr;
          std::string epicBgColor{};
          if (epicPtr != nullptr) {
            epicBgColor = epicPtr->bgColor;
          }

          return mstch::map{
              {"balance",       epicContainer.getBalanceStr()},
              {"balance_class", epicContainer.getBalanceHtmlClass()},
              {"epic_bg_color", std::move(epicBgColor)},
          };
        } catch (const std::out_of_range& exception) {
          DLog("-> nothing found for epic '%s'\n", pair.first.c_str());

          return mstch::map{
              {"balance",       std::string("&nbsp;")},
              {"balance_class", std::string()},
              {"epic_bg_color", std::string("#ffffff")},
          };
        }
      });

      // Month Map
      mstch::map monthMap{
          {"file_name",        monthHtml.getFileName()},
          {"month_name",       monthHtml.name},
          {"revenue",          monthPair.second.getRevenueStr()},
          {"expense",          monthPair.second.getExpenseStr()},
          {"balance",          monthPair.second.getBalanceStr()},
          {"balance_class",    monthPair.second.getBalanceHtmlClass()},
          {"month_categories", std::move(monthCategories)},
          {"month_epics",      std::move(monthEpics)},
      };
      entries.push_back(monthMap);
    } // this->container.months

    // Match common categories to total month categories.
    mstch::array totalCategories{};
    std::transform(_categories_begin, _categories_end, std::back_inserter(totalCategories), [](const auto& pair) {
      //DLog("-> category: '%s'\n", pair.first.c_str());

      return mstch::map{
          {"balance",         pair.second.getBalanceStr()},
          {"balance_class",   pair.second.getBalanceHtmlClass()},
          {"balance_percent", pair.second.getBalancePercentStr()},
      };
    });

    // Total Epics
    mstch::array totalEpics{};
    std::transform(_epics_begin, _epics_end, std::back_inserter(totalEpics), [](const auto& pair) {
      //DLog("-> transform total epic: '%s'\n", pair.first.c_str());

      const auto& epicContainer = pair.second;
      const auto& epicPtr = epicContainer.epicPtr;

      std::string epicBgColor{"#ffffff"};

      if (epicPtr != nullptr) {
        epicBgColor = epicPtr->bgColor;
      }

      return mstch::map{
          {"name",            pair.first},
          //{"revenue_percent", pair.second.getRevenuePercentStr()},
          //{"expense_percent", pair.second.getExpensePercentStr()},
          {"balance",         epicContainer.getBalanceStr()},
          {"balance_class",   epicContainer.getBalanceHtmlClass()},
          {"balance_percent", epicContainer.getBalancePercentStr()},
          {"epic_bg_color",   std::move(epicBgColor)},
      };
    });

    const auto yearFileStr = "year_" + yearStr;
    const auto yearPngFileStr = yearFileStr + ".png";

    // Total Map
    const mstch::map total{
        {"label",            std::string{"TOTAL"}},
        {"revenue",          this->container.getRevenueStr()},
        {"revenue_percent",  this->container.getRevenuePercentStr()},
        {"expense",          this->container.getExpenseStr()},
        {"expense_percent",  this->container.getExpensePercentStr()},
        {"balance",          this->container.getBalanceStr()},
        {"balance_class",    this->container.getBalanceHtmlClass()},
        //{"balance_percent", std::string{"getBalancePercentStr"}},
        {"total_categories", std::move(totalCategories)},
        {"total_epics",      std::move(totalEpics)},
    };

    const auto tpl = Components::readFileIntoString(WALLETCPP_YEAR_VIEW_PATH);
    const auto context = std::make_shared<Mustache::YearMustache>("../..", entries, total, yearStr, categories,
        epicPtrs, yearPngFileStr);

    // Year HTML File Output
    std::ofstream indexFh{this->getFullPath()};
    indexFh << mstch::render(tpl, context) << '\n';
    indexFh.close();

#ifdef WALLETCPP_GNUPLOT_SUPPORT
    const auto monthsBegin = this->container.months.cbegin();
    const auto monthsEnd = this->container.months.cend();

    // Balance Sum
    Trait::Accountable::Number balanceSum{0.0};

    std::vector<std::string> datRows{};
    std::transform(monthsBegin, monthsEnd, std::back_inserter(datRows), [&balanceSum](const auto& pair) {
      const auto& monthEntryContainer = pair.second;
      const auto revenue = monthEntryContainer.getRevenueStr();
      const auto expense = monthEntryContainer.getExpenseStr();
      const auto balance = monthEntryContainer.getBalanceStr();

      // Balance Sum
      balanceSum += monthEntryContainer.balance;

      std::string row{monthEntryContainer.yearMonth};
      row += " " + (revenue.empty() ? "0" : revenue);
      row += " " + (expense.empty() ? "0" : expense);
      row += " " + (balance.empty() ? "0" : balance);
      row += " " + std::to_string(balanceSum);

      return row;
    });

    const auto yearDatFileStr = yearFileStr + ".dat";

    // TODO: path fix
    const auto pngFilePath = (this->basePath / yearPngFileStr).string();
    const auto datFilePath = (this->tmpPath / yearDatFileStr).string();

    DLog("-> png: '%s'\n", pngFilePath.c_str());
    DLog("-> dat: '%s'\n", datFilePath.c_str());

    // Write data file for GNUPlot.
    std::ofstream datFh{datFilePath};
    std::copy(datRows.cbegin(), datRows.cend(), std::ostream_iterator<std::string>(datFh, "\n"));
    datFh.close();

    // Mustache Template file
    const auto gnuplotTpl = Components::readFileIntoString(WALLETCPP_YEAR_GNUPLOT_PATH);

    // Mustache Context
    const auto gnuplotContext = std::make_shared<Mustache::YearGnuplot>(yearStr, pngFilePath, datFilePath);

    // Year Gnuplot File
    // TODO: path fix
    const auto gnuplotFilePath = (this->tmpPath / (yearFileStr + ".gp")).string();
    DLog("-> gnuplotFilePath: '%s'\n", gnuplotFilePath.c_str());

    std::ofstream totalFh{gnuplotFilePath};
    totalFh << mstch::render(gnuplotTpl, gnuplotContext) << '\n';
    totalFh.close();

    // Run GNUPlot
    const auto gnuplotCmd = std::string{"gnuplot "} + gnuplotFilePath + " &> /dev/null < /dev/null";

#ifdef DEBUG
    DLog("-> exec gnuplot: '%s'\n", gnuplotCmd.c_str());
    const auto execrv = std::system(gnuplotCmd.c_str());
    DLog("-> exec gnuplot: %d\n", execrv);
#else
    std::system(gnuplotCmd.c_str());
#endif
#endif
  }
} // Wallet::Html Namespace
