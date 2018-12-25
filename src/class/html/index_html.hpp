
#ifndef WALLETCPP_HTML_INDEX_HTML_HPP_
#define WALLETCPP_HTML_INDEX_HTML_HPP_

#include <string>

#include "base_html.hpp"

namespace Wallet::Html
{
  struct IndexHtmlRow
  {
    const std::string year{};
    const std::string revenue{};
    const std::string expense{};
    const std::string balance{};
    const std::string balanceClass{};
    const std::string balanceSum{};
    const std::string balanceSumClass{};
  };

  class IndexMustacheObject final : public BaseMustacheObject
  {
  public:
    // Constructor
    IndexMustacheObject(mstch::array, mstch::map);
  };

  /**
   * Generates the main index.html file.
   */
  class IndexHtml final : public BaseHtml
  {
  public:
    explicit IndexHtml(fs::path);
    void addRow(IndexHtmlRow) noexcept;
    void generate(IndexHtmlRow) const;

  private:
    // Properties
    mstch::array entries{};
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_INDEX_HTML_HPP_
