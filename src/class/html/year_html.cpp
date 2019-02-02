
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
    //DLog(" -> YearHtml::YearHtml('%s', '%s')\n", this->basePath.c_str(), this->getFileName().c_str());
  }

  void YearHtml::generate() const
  {
    //DLog(" -> YearHtml::generate() -> %d\n", this->container.year);
    const auto yearStr = std::to_string(this->container.year);
    this->log("[year_html] generate: " + yearStr);

    if (!fs::exists(WALLETCPP_YEAR_VIEW_PATH)) {
      DLog("ERROR: Year template file does not exists: '%s'\n", WALLETCPP_YEAR_VIEW_PATH);
      throw std::string{"Year template file does not exists: "} + WALLETCPP_YEAR_VIEW_PATH;
    }

    // Categories Iterators
    const auto cib = this->container.categories.cbegin();
    const auto cie = this->container.categories.cend();

    // Category Names
    Container::CategoryArray categoryNames{};

    // https://thispointer.com/how-to-copy-all-values-from-a-map-to-a-vector-in-c/
    std::transform(cib, cie, std::back_inserter(categoryNames), [](const auto& pair) {
      return pair.first;
    });

    // Table Body
    mstch::array entries{};

    for (const auto& monthPair : this->container.months) {
      const MonthHtml monthHtml{this->basePath, monthPair};
      monthHtml.logLevel = this->logLevel;
      monthHtml.generate();

      // Match common categories to month categories.
      mstch::array monthCategories{};
      std::transform(cib, cie, std::back_inserter(monthCategories), [&monthPair](const auto& pair) {
        std::string balance{"&nbsp;"};
        std::string balanceClass{};

        try {
          // Search by key (Name).
          const auto& category = monthPair.second.categories.at(pair.first);
          //DLog(" -> category found: '%s'\n", pair.first.c_str());

          balance = category.getBalanceStr();
          balanceClass = category.getBalanceHtmlClass();
        } catch (const std::out_of_range& exception) {
          //DLog(" -> nothing found for category '%s'\n", pair.first.c_str());
        }

        return mstch::map{
          {"balance",       std::move(balance)},
          {"balance_class", std::move(balanceClass)},
        };
      });

      mstch::map monthMap{
        {"file_name",        monthHtml.getFileName()},
        {"month_name",       monthHtml.name},
        {"revenue",          monthPair.second.getRevenueStr()},
        {"expense",          monthPair.second.getExpenseStr()},
        {"balance",          monthPair.second.getBalanceStr()},
        {"balance_class",    monthPair.second.getBalanceHtmlClass()},
        {"month_categories", std::move(monthCategories)},
      };
      entries.push_back(monthMap);
    } // this->container.months

    // Match common categories to total month categories.
    mstch::array monthCategories{};
    std::transform(cib, cie, std::back_inserter(monthCategories), [](const auto& pair) {
      //DLog(" -> category: '%s'\n", pair.first.c_str());

      return mstch::map{
        {"balance",       pair.second.getBalanceStr()},
        {"balance_class", pair.second.getBalanceHtmlClass()},
      };
    });

    const auto yearFileStr = "year_" + yearStr;
    const auto yearPngFileStr = yearFileStr + ".png";

    const mstch::map total{
      {"label",            std::string{"TOTAL"}},
      {"revenue",          this->container.getRevenueStr()},
      {"expense",          this->container.getExpenseStr()},
      {"balance",          this->container.getBalanceStr()},
      {"balance_class",    this->container.getBalanceHtmlClass()},
      {"month_categories", std::move(monthCategories)},
    };

    const auto tpl = Components::readFileIntoString(WALLETCPP_YEAR_VIEW_PATH);
    const auto context = std::make_shared<Mustache::YearMustache>("../..", entries, total, yearStr, categoryNames,
      yearPngFileStr);

    // Year HTML File Output
    std::ofstream indexFh{this->getFullPath()};
    indexFh << mstch::render(tpl, context) << '\n';
    indexFh.close();

#ifdef WALLETCPP_GNUPLOT_SUPPORT
    const auto monthsBegin = this->container.months.cbegin();
    const auto monthsEnd = this->container.months.cend();

    // Balance Sum
    Accountable::Number balanceSum{0.0};

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

    const auto pngFilePath = (this->basePath / yearPngFileStr).string();
    const auto datFilePath = (this->tmpPath / yearDatFileStr).string();

    DLog(" -> png: '%s'\n", pngFilePath.c_str());
    DLog(" -> dat: '%s'\n", datFilePath.c_str());

    // Write data file for GNUPlot.
    std::ofstream datFh{datFilePath};
    std::copy(datRows.cbegin(), datRows.cend(), std::ostream_iterator<std::string>(datFh, "\n"));
    datFh.close();

    // Mustache Template file
    const auto gnuplotTpl = Components::readFileIntoString(WALLETCPP_YEAR_GNUPLOT_PATH);

    // Mustache Context
    const auto gnuplotContext = std::make_shared<Mustache::YearGnuplot>(yearStr, pngFilePath, datFilePath);

    // Year Gnuplot File
    const auto gnuplotFilePath = (this->tmpPath / (yearFileStr + ".gp")).string();
    DLog(" -> gp: '%s'\n", gnuplotFilePath.c_str());
    std::ofstream totalFh{gnuplotFilePath};
    totalFh << mstch::render(gnuplotTpl, gnuplotContext) << '\n';
    totalFh.close();

    // Run GNUPlot
    const auto gnuplotCmd = std::string{"gnuplot "} + gnuplotFilePath + " &> /dev/null < /dev/null";

#ifdef DEBUG
    DLog(" -> exec gnuplot: '%s'\n", gnuplotCmd.c_str());
    const auto execrv = std::system(gnuplotCmd.c_str());
    DLog(" -> exec gnuplot: %d\n", execrv);
#else
    std::system(gnuplotCmd.c_str());
#endif
#endif
  }
} // Wallet::Html Namespace
