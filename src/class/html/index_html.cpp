
#include <memory> // make_shared

#include "debug.hpp"
#include "index_html.hpp"
#include "components.hpp"

namespace Wallet::Html
{
  IndexMustacheObject::IndexMustacheObject(mstch::array _entries, mstch::map _total) :
    //entries(std::move(_entries)), total(std::move(_total))
    BaseMustacheObject(std::move(_entries), std::move(_total))
  {
    DLog(" -> IndexMustacheObject::IndexMustacheObject()\n");
  }

  IndexHtml::IndexHtml(fs::path _basePath) :
    BaseHtml{std::move(_basePath), fs::path{"index.html"}, "Index"}
  {
    DLog(" -> IndexHtml::IndexHtml('%s')\n", this->basePath.c_str());
  }

  void IndexHtml::addRow(const IndexHtmlRow row) noexcept
  {
    DLog(" -> IndexHtml::addRow(%s)\n", row.year.c_str());

    const mstch::map rowMap{
      {"year", row.year},
      {"revenue", row.revenue},
      {"expense", row.expense},
      {"balance", row.balance},
      {"balance_class", row.balanceClass},
      {"balance_sum", row.balanceSum},
      {"balance_sum_class", row.balanceSumClass},
    };
    this->entries.push_back(rowMap);
  }

  void IndexHtml::generate(const IndexHtmlRow totalRow)
  {
    DLog(" -> IndexHtml::generate('%s')\n", totalRow.year.c_str());

    if (!fs::exists(WALLETCPP_INDEX_VIEW_PATH)) {
      throw std::string{"Index template file does not exists: "} + WALLETCPP_INDEX_VIEW_PATH;
    }

    const std::string tpl = Components::readFileIntoString(WALLETCPP_INDEX_VIEW_PATH);

    const mstch::map total{
      {"year", totalRow.year},
      {"revenue", totalRow.revenue},
      {"expense", totalRow.expense},
      {"balance", totalRow.balance},
      {"balance_class", totalRow.balanceClass},
    };

    const auto context = std::make_shared<IndexMustacheObject>(this->entries, total);

    // Output: index.html
    std::ofstream indexFh{this->getFullPath()};
    indexFh << mstch::render(tpl, context);
    indexFh.close();
  }
} // Wallet::Html Namespace
