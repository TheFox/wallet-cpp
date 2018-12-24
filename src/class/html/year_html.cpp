
#include <fstream> // ofstream
#include <string>

#include "debug.hpp"
#include "components.hpp"
#include "year_html.hpp"
#include "month_html.hpp"

namespace Wallet::Html
{
  YearMustacheObject::YearMustacheObject(std::string _rel, mstch::array _entries, mstch::map _total,
                                         std::string _year) :
    BaseMustacheObject(std::move(_rel), std::move(_entries), std::move(_total)), year(std::move(_year))
  {
    DLog(" -> YearMustacheObject::YearMustacheObject('%s', '%s')\n", _rel.c_str(), this->year.c_str());

    this->register_methods(this, {
      {"year", &YearMustacheObject::getYear},
      {"category_count", &YearMustacheObject::getCategoryCount},
    });
  }

  mstch::node YearMustacheObject::getYear() noexcept
  {
    DLog(" -> YearMustacheObject::getYear()\n");
    return this->year;
  }

  mstch::node YearMustacheObject::getCategoryCount() noexcept
  {
    DLog(" -> YearMustacheObject::getCategoryCount()\n");
    return std::string{"2"}; // TODO
  }

  YearHtml::YearHtml(fs::path _basePath, Wallet::Container::YearEntryContainer _container) :
    BaseHtml{std::move(_basePath), fs::path{"index.html"}, "Year " + std::to_string(_container.year)},
    container(std::move(_container))
  {
    DLog(" -> YearHtml::YearHtml('%s', '%s')\n", this->basePath.c_str(), this->getFileName().c_str());
  }

  void YearHtml::generate() const
  {
    DLog(" -> YearHtml::generate()\n");

    const auto categoryCountStr = std::to_string(this->container.categories.size());

    // Table Body
    //CTML::Node tableBody("tbody");

    for (const auto& monthPair : this->container.months) {
      //MonthHtml monthHtml{this->basePath, monthPair};
      //monthHtml.generate();

      //CTML::Node monthTd{"td.left"};
      //monthTd.AppendChild(
      //  CTML::Node("a", monthHtml.name).SetAttribute("href", monthHtml.getFileName()));

      //CTML::Node tableRow{"tr"};
      //tableRow.AppendChild(monthTd);
      //tableRow.AppendChild(CTML::Node{"td.right", monthPair.second.getRevenueStr()});
      //tableRow.AppendChild(CTML::Node{"td.right red", monthPair.second.getExpenseStr()});
      //tableRow.AppendChild(
      //  CTML::Node{"td.right " + monthPair.second.getBalanceHtmlClass(), monthPair.second.getBalanceStr()});

      for (const auto& categoryPair : this->container.categories) {
        try {
          const auto& category = monthPair.second.categories.at(categoryPair.first);
          //CTML::Node categoryTd{"td.right " + category.getBalanceHtmlClass(), category.getBalanceStr()};
          //tableRow.AppendChild(categoryTd);
        }
        catch (const std::out_of_range& exception) {
          //tableRow.AppendChild(CTML::Node{"td", " "});
        }
      }
    }

    // Total Columns
    //totalTr.AppendChild(CTML::Node{"td.right", this->container.getRevenueStr()});
    //totalTr.AppendChild(CTML::Node{"td.right red", this->container.getExpenseStr()});
    //totalTr.AppendChild(
    //  CTML::Node{"td.right " + this->container.getBalanceHtmlClass(), this->container.getBalanceStr()});
    //for (const auto& categoryPair : this->container.categories) {
      //totalTr.AppendChild(
      //  CTML::Node{"td.right " + categoryPair.second.getBalanceHtmlClass(), categoryPair.second.getBalanceStr()});
    //}

    // Table Head Row
    //CTML::Node tableHeadTr1{"tr"};
    //CTML::Node categoryTh{"th.right", categoryCountStr + " Categories"};
    //categoryTh.SetAttribute("colspan", categoryCountStr);
    //tableHeadTr1.AppendChild(categoryTh);

    // Table Head Categories
    //CTML::Node tableHeadTr2{"tr"};
    //tableHeadTr2.AppendChild(CTML::Node{"th", " "}.SetAttribute("colspan", "4"));
    //for (const auto& categoryPair : this->container.categories) {
      //tableHeadTr2.AppendChild(CTML::Node{"th.left", categoryPair.first});
    //}

    if (!fs::exists(WALLETCPP_YEAR_VIEW_PATH)) {
      throw std::string{"Year template file does not exists: "} + WALLETCPP_YEAR_VIEW_PATH;
    }

    const std::string tpl = Components::readFileIntoString(WALLETCPP_YEAR_VIEW_PATH);

    mstch::array entries{};

    const auto yearStr=std::to_string(this->container.year);

    const mstch::map total{
      {"year", std::string{"TOTAL"}},
      {"revenue", std::string{"N/A"}},
      {"expense", std::string{"N/A"}},
      {"balance", std::string{"N/A"}},
      {"balance_class", std::string{"N/A"}},
    };

    const auto context = std::make_shared<YearMustacheObject>("../..", entries, total, yearStr);

    // Output: index.html
    std::ofstream indexFh{this->getFullPath()};
    indexFh << mstch::render(tpl, context);
    indexFh.close();
  }
} // Wallet::Html Namespace
