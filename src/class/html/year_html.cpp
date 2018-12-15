
#include <fstream> // ofstream

#include "year_html.hpp"
#include "../../debug.hpp"
#include "month_html.hpp"

namespace Wallet::Html
{
  YearHtml::YearHtml(fs::path _path, Wallet::Container::YearEntryContainer _container)
    : BaseHtml{_path / "index.html"}, basePath(std::move(_path)), container(std::move(_container))
  {
    DLog(" -> YearHtml::YearHtml(%s)\n", this->path.c_str());
  }

  void YearHtml::generate() const noexcept
  {
    DLog(" -> YearHtml::generate()\n");

    // Table Body
    CTML::Node tableBody("tbody");

    for (const auto& monthPair : this->container.months) {
      DLog("   -> month pair\n");

      const auto monthStr = std::to_string(monthPair.first);

      std::stringstream monthFilePathSs;
      monthFilePathSs << "month_";
      monthFilePathSs << std::setfill('0') << std::setw(2) << monthStr;
      monthFilePathSs << ".html";
      const auto monthFilePath = monthFilePathSs.str();

      //this->htmlOutputMonth(, yearDirPath / monthFilePath);
      MonthHtml monthHtml{"MONTHNAME", this->basePath, monthPair}; // TODO
      monthHtml.generate();

      CTML::Node monthTd{"td.left"};
      monthTd.AppendChild(CTML::Node("a", "Month " + monthStr).SetAttribute("href", monthFilePath));

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
    auto indexDoc = BaseHtml::getHtmlDoc("../../index.html");
    indexDoc.AppendNodeToBody(indexTable);

    // Output: index.html
    DLog(" -> write year index file\n");
    std::ofstream indexFh{};
    indexFh.open(this->path.string(), std::ofstream::out);
    indexFh << indexDoc.ToString(CTML::StringFormatting::MULTIPLE_LINES); // TODO
    indexFh.close();
  }
} // Wallet::Html Namespace
