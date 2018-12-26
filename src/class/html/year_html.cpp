
#include <fstream> // ofstream
#include <string>
#include <iterator> // back_inserter
#include <algorithm> // transform

#include "debug.hpp"
#include "config.hpp"
#include "components.hpp"
#include "year_html.hpp"
#include "month_html.hpp"
#include "class/mustache/year_mustache.hpp"
#ifdef WALLETCPP_GNUPLOT_SUPPORT
//#include "class/mustache/"
#endif

namespace Wallet::Html
{
  YearHtml::YearHtml(fs::path _basePath, Container::YearEntryContainer _container) :
    BaseHtml{std::move(_basePath), fs::path{}, fs::path{"index.html"}, "Year " + std::to_string(_container.year)},
    container(std::move(_container))
  {
    //DLog(" -> YearHtml::YearHtml('%s', '%s')\n", this->basePath.c_str(), this->getFileName().c_str());
  }

  void YearHtml::generate() const
  {
    //DLog(" -> YearHtml::generate() -> %d\n", this->container.year);

    if (!fs::exists(WALLETCPP_YEAR_VIEW_PATH)) {
      DLog("ERROR: Year template file does not exists: '%s'\n", WALLETCPP_YEAR_VIEW_PATH);
      throw std::string{"Year template file does not exists: "} + WALLETCPP_YEAR_VIEW_PATH;
    }

    // Category Names
    Container::CategoryArray categoryNames{};

    // https://thispointer.com/how-to-copy-all-values-from-a-map-to-a-vector-in-c/
    std::transform(this->container.categories.cbegin(), this->container.categories.cend(),
      std::back_inserter(categoryNames),
      [](const auto& pair) {
        return pair.first;
      });

    // Table Body
    mstch::array entries{};

    // Categories Iterators
    const auto cib = this->container.categories.cbegin();
    const auto cie = this->container.categories.cend();

    for (const auto& monthPair : this->container.months) {
      MonthHtml monthHtml{this->basePath, monthPair};
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
    std::transform(cib, cie, std::back_inserter(monthCategories), [&](const auto& pair) {
      //DLog(" -> category: '%s'\n", pair.first.c_str());

      return mstch::map{
        {"balance",       pair.second.getBalanceStr()},
        {"balance_class", pair.second.getBalanceHtmlClass()},
      };
    });

    const auto yearStr = std::to_string(this->container.year);

    const mstch::map total{
      {"label",            std::string{"TOTAL"}},
      {"revenue",          this->container.getRevenueStr()},
      {"expense",          this->container.getExpenseStr()},
      {"balance",          this->container.getBalanceStr()},
      {"balance_class",    this->container.getBalanceHtmlClass()},
      {"month_categories", std::move(monthCategories)},
    };

    const std::string tpl = Components::readFileIntoString(WALLETCPP_YEAR_VIEW_PATH);
    const auto context = std::make_shared<Mustache::YearMustache>("../..", entries, total, yearStr, categoryNames);

    // Year File Output
    std::ofstream indexFh{this->getFullPath()};
    indexFh << mstch::render(tpl, context);
    indexFh.close();

#ifdef WALLETCPP_GNUPLOT_SUPPORT
    //DLog(" -> YearHtml::generate() -> GNUPlot support\n");
    // TODO
#endif
  }
} // Wallet::Html Namespace
