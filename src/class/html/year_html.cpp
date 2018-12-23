
#include <fstream> // ofstream
#include <string>

#include "debug.hpp"
#include "year_html.hpp"
#include "month_html.hpp"

namespace Wallet::Html
{
  YearHtml::YearHtml(fs::path _basePath, Wallet::Container::YearEntryContainer _container) :
    BaseHtml{std::move(_basePath), fs::path{"index.html"}, "Year " + std::to_string(_container.year)},
    container(std::move(_container))
  {
    //DLog(" -> YearHtml::YearHtml('%s', '%s')\n", this->getBasePath().c_str(), this->getFileName().c_str());
  }

  void YearHtml::generate() const noexcept
  {
    //DLog(" -> YearHtml::generate()\n");

    const auto categoryCountStr = std::to_string(this->container.categories.size());

    // Table Body
    CTML::Node tableBody("tbody");

    for (const auto& monthPair : this->container.months) {
      //DLog("   -> month pair\n");

      MonthHtml monthHtml{this->basePath, monthPair};
      monthHtml.generate();

      CTML::Node monthTd{"td.left"};
      monthTd.AppendChild(
        CTML::Node("a", monthHtml.name).SetAttribute("href", monthHtml.getFileName()));

      CTML::Node tableRow{"tr"};
      tableRow.AppendChild(monthTd);
      tableRow.AppendChild(CTML::Node{"td.right", monthPair.second.getRevenueStr()});
      tableRow.AppendChild(CTML::Node{"td.right red", monthPair.second.getExpenseStr()});
      tableRow.AppendChild(CTML::Node{"td.right", monthPair.second.getBalanceStr()});
      tableRow.AppendChild(CTML::Node{"td", "CAT1"});
      tableRow.AppendChild(CTML::Node{"td", "CAT1"});
      tableRow.AppendChild(CTML::Node{"td", "CAT1"}); // TODO
      tableBody.AppendChild(tableRow);
    }

    // Total Row
    CTML::Node totalTr{"tr"};

    // Total Columns
    totalTr.AppendChild(CTML::Node{"td left", "TOTAL"});
    totalTr.AppendChild(CTML::Node{"td right", this->container.getRevenueStr()});
    totalTr.AppendChild(CTML::Node{"td right red", this->container.getExpenseStr()});
    totalTr.AppendChild(CTML::Node{"td right", this->container.getBalanceStr()});
    totalTr.AppendChild(CTML::Node{"td", "CAT2"});
    totalTr.AppendChild(CTML::Node{"td", "CAT2"});
    totalTr.AppendChild(CTML::Node{"td", "CAT2"}); // TODO

    // Table Head Row
    CTML::Node tableHeadTr1{"tr"};
    tableHeadTr1.AppendChild(CTML::Node{"th.left", "Month"});
    tableHeadTr1.AppendChild(CTML::Node{"th.right", "Revenue"});
    tableHeadTr1.AppendChild(CTML::Node{"th.right", "Expense"});
    tableHeadTr1.AppendChild(CTML::Node{"th.right", "Balance"});
    tableHeadTr1.AppendChild(CTML::Node{"th.right", categoryCountStr + " Categories"}.SetAttribute("colspan", categoryCountStr));

    // Table Head Categories
    CTML::Node tableHeadTr2{"tr"};
    tableHeadTr2.AppendChild(CTML::Node{"th", "NIX"}.SetAttribute("colspan", "4"));
    for (const auto& categoryPair : this->container.categories){
      //DLog("   -> category pair: %s\n", categoryPair.first.c_str());
      tableHeadTr2.AppendChild(CTML::Node{"th", categoryPair.first});
    }

    // Table Head
    CTML::Node tableHead{"thead"};
    tableHead.AppendChild(tableHeadTr1);
    tableHead.AppendChild(tableHeadTr2);

    // Table Footer
    CTML::Node tableFoot{"tfoot"};
    tableFoot.AppendChild(totalTr);

    // Table
    CTML::Node table{"table.list"};
    table.SetAttribute("border", "1"); // TODO
    table.AppendChild(tableHead);
    table.AppendChild(tableBody);
    table.AppendChild(tableFoot);

    // Year Doc
    auto yearDoc = this->getHtmlDoc("../../index.html");
    yearDoc.AppendNodeToBody(CTML::Node{"h2", this->title});
    yearDoc.AppendNodeToBody(table);

    // Output: index.html
    //DLog(" -> write year index file\n");
    std::ofstream indexFh{};
    indexFh.open(this->getFullPath(), std::ofstream::out);
    indexFh << yearDoc.ToString(CTML::StringFormatting::MULTIPLE_LINES); // TODO
    indexFh.close();
  }
} // Wallet::Html Namespace
