
#include <fstream> // ofstream
#include <string>

#include "year_html.hpp"
#include "../../debug.hpp"
#include "month_html.hpp"

namespace Wallet { namespace Html
{
  YearHtml::YearHtml(boost::filesystem::path _basePath, Wallet::Container::YearEntryContainer _container) :
    BaseHtml{std::move(_basePath), boost::filesystem::path{"index.html"}, "Year " + std::to_string(_container.year)},
    container(std::move(_container))
  {
    //DLog(" -> YearHtml::YearHtml('%s', '%s')\n", this->getBasePath().c_str(), this->getFileName().c_str());
  }

  void YearHtml::generate() const noexcept
  {
    //DLog(" -> YearHtml::generate()\n");

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
      tableBody.AppendChild(tableRow);
    }

    // Total Row
    CTML::Node totalTr{"tr"};

    // Total Columns
    totalTr.AppendChild(CTML::Node{"td.left", "TOTAL"});
    totalTr.AppendChild(CTML::Node{"td.right", this->container.getRevenueStr()});
    totalTr.AppendChild(CTML::Node{"td.right red", this->container.getExpenseStr()});
    totalTr.AppendChild(CTML::Node{"td.right", this->container.getBalanceStr()});

    // Table Head Row
    CTML::Node tableHeadTr{"tr"};
    tableHeadTr.AppendChild(CTML::Node{"th.left", "Month"});
    tableHeadTr.AppendChild(CTML::Node{"th.right", "Revenue"});
    tableHeadTr.AppendChild(CTML::Node{"th.right", "Expense"});
    tableHeadTr.AppendChild(CTML::Node{"th.right", "Balance"});

    // Table Head
    CTML::Node tableHead{"thead"};
    tableHead.AppendChild(tableHeadTr);

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
}} // Wallet::Html Namespace
