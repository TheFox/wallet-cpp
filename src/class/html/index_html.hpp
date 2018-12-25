
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

    // Functions
    mstch::node hasGnuplotSupport() noexcept;
  };

  class TotalGnuplotObject final : public BaseGnuplotObject
  {
  public:
    // Constructor
    TotalGnuplotObject(std::string, std::string);

  private:
    // Functions
    mstch::node getPngFilePath() noexcept;
    mstch::node getDatFilePath() noexcept;

    // Properties
    const std::string pngFilePath{};
    const std::string datFilePath{};
  };

  /**
   * Generates the main index.html file.
   */
  class IndexHtml final : public BaseHtml
  {
  public:
    // Constructor
    explicit IndexHtml(fs::path, fs::path);

    // Functions
    void addRow(IndexHtmlRow) noexcept;
    void generate(IndexHtmlRow) const;

  private:
    // Properties
    mstch::array entries{};
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_INDEX_HTML_HPP_
