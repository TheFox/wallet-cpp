
#include "index_html.hpp"
#include "../../debug.hpp"

namespace Wallet::Html
{
  IndexHtml::IndexHtml(fs::path _basePath) :
    BaseHtml{std::move(_basePath), fs::path{"index.html"}, "Index"}
  {
    //DLog(" -> IndexHtml::IndexHtml('%s')\n", this->getBasePath().c_str());
  }

  void IndexHtml::addRow(const IndexHtmlRow row)
  {
    //DLog(" -> IndexHtml::addRow()\n");

    CTML::Node yearTd{"td.left"};
    yearTd.AppendChild(CTML::Node("a", row.year)
      .SetAttribute("href", "year/" + row.year + "/"));

    const CTML::Node revenueTd{"td.right", row.revenue};

    CTML::Node tableRow{"tr"};
    tableRow.AppendChild(yearTd);
    tableRow.AppendChild(revenueTd);
    tableRow.AppendChild(CTML::Node{"td.right red", row.expense});
    tableRow.AppendChild(CTML::Node{"td.right", row.balance});
    tableRow.AppendChild(CTML::Node{"td.right", row.balanceSum});

    // Add to Table.
    this->tableBody.AppendChild(tableRow);
  }

  void IndexHtml::generate(const IndexHtmlRow row)
  {
    DLog(" -> IndexHtml::generate()\n");

    CTML::Node tableRow{"tr"};
    tableRow.AppendChild(CTML::Node{"td.left", "TOTAL"});
    tableRow.AppendChild(CTML::Node{"td.right", row.revenue});
    tableRow.AppendChild(CTML::Node{"td.right red", row.expense});
    tableRow.AppendChild(CTML::Node{"td.right", row.balance});
    tableRow.AppendChild(CTML::Node{"td.right", " "});
    tableBody.AppendChild(tableRow);

    // Index Table Head Row
    CTML::Node indexTableHeadTr{"tr"};
    indexTableHeadTr.AppendChild(CTML::Node{"th.left", "Year"});
    indexTableHeadTr.AppendChild(CTML::Node{"th.right", "Revenue"});
    indexTableHeadTr.AppendChild(CTML::Node{"th.right", "Expense"});
    indexTableHeadTr.AppendChild(CTML::Node{"th.right", "Balance"});
    indexTableHeadTr.AppendChild(CTML::Node{"th.right", "Balance &#8721;"});

    // Index Table Head
    CTML::Node indexTableHead{"thead"};
    indexTableHead.AppendChild(indexTableHeadTr);

    // Index Table
    CTML::Node indexTable{"table.list"};
    indexTable.SetAttribute("border", "1"); // TODO
    indexTable.AppendChild(indexTableHead);
    indexTable.AppendChild(tableBody);

    // Index Doc
    auto indexDoc = BaseHtml::getHtmlDoc();
    indexDoc.AppendNodeToBody(indexTable);

    // Output: index.html
    std::ofstream indexFh{};
    indexFh.open(this->getFullPath(), std::ofstream::out);
    indexFh << indexDoc.ToString(CTML::StringFormatting::MULTIPLE_LINES); // TODO
    indexFh.close();
  }
} // Wallet::Html Namespace
