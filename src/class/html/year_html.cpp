
#include <fstream> // ofstream
#include <string>

#include "year_html.hpp"
#include "../../debug.hpp"
#include "month_html.hpp"

namespace Wallet::Html
{
  YearHtml::YearHtml(fs::path _path, Wallet::Container::YearEntryContainer _container)
    : BaseHtml{_path / "index.html", "Year " + std::to_string(_container.year)}, basePath(std::move(_path)), container(std::move(_container))
  {
    DLog(" -> YearHtml::YearHtml('%s')\n", this->path.c_str());
  }

  void YearHtml::generate() const noexcept
  {
    DLog(" -> YearHtml::generate()\n");

    // Table Body
    CTML::Node tableBody("tbody");

    for (const auto& monthPair : this->container.months) {
      DLog("   -> month pair\n");

      MonthHtml monthHtml{this->basePath, monthPair, std::to_string(this->container.year)};
      monthHtml.generate();

      CTML::Node monthTd{"td.left"};
      monthTd.AppendChild(
        CTML::Node("a", monthHtml.name).SetAttribute("href", monthHtml.path.string()));

      CTML::Node tableRow{"tr"};
      tableRow.AppendChild(monthTd);
      tableRow.AppendChild(CTML::Node{"td.right", monthPair.second.getRevenueStr()});
      tableRow.AppendChild(CTML::Node{"td.right red", monthPair.second.getExpenseStr()});
      tableRow.AppendChild(CTML::Node{"td.right", monthPair.second.getBalanceStr()});
      tableBody.AppendChild(tableRow);
    }

    // Index Table Head Row
    CTML::Node indexTableHeadTr{"tr"};
    indexTableHeadTr.AppendChild(CTML::Node{"th.left", "Month"});
    indexTableHeadTr.AppendChild(CTML::Node{"th.right", "Revenue"});
    indexTableHeadTr.AppendChild(CTML::Node{"th.right", "Expense"});
    indexTableHeadTr.AppendChild(CTML::Node{"th.right", "Balance"});

    // Index Table Head
    CTML::Node indexTableHead{"thead"};
    indexTableHead.AppendChild(indexTableHeadTr);

    // Index Table
    CTML::Node indexTable{"table.list"};
    indexTable.SetAttribute("border", "1"); // TODO
    indexTable.AppendChild(indexTableHead);
    indexTable.AppendChild(tableBody);

    // Index Doc
    auto indexDoc = this->getHtmlDoc("../../index.html");
    indexDoc.AppendNodeToBody(indexTable);

    // Output: index.html
    DLog(" -> write year index file\n");
    std::ofstream indexFh{};
    indexFh.open(this->path.string(), std::ofstream::out);
    indexFh << indexDoc.ToString(CTML::StringFormatting::MULTIPLE_LINES); // TODO
    indexFh.close();
  }
} // Wallet::Html Namespace
