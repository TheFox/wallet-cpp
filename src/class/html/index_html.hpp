
#ifndef WALLETCPP_HTML_INDEX_HTML_HPP_
#define WALLETCPP_HTML_INDEX_HTML_HPP_

#include <string>
#include <vector>

#ifdef __has_include
#  if __has_include(<mstch/mstch.hpp>)
#    include <mstch/mstch.hpp>
#  else
#    error "Missing <mstch/mstch.hpp>"
#  endif
#endif // __has_include

#include "config.hpp"
#include "base_html.hpp"
#include "class/container/entry_container.hpp"
#include "class/container/epic_container.hpp"

namespace Wallet::Html
{
  struct IndexHtmlRow
  {
    const std::string year{};
    const std::string revenue{};
    const std::string revenuePercent{};
    const std::string expense{};
    const std::string expensePercent{};
    const std::string balance{};
    const std::string balanceClass{};
    const std::string balanceSum{};
    const std::string balanceSumClass{};

    const mstch::array categories{};
    const mstch::array epics{};
  };

  using IndexHtmlRows = std::vector<IndexHtmlRow>;

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
    void generate(IndexHtmlRow, const Container::CategoryMap&, const Container::EpicMap&) const;

  private:
    // Properties
    IndexHtmlRows entries{};

#ifdef WALLETCPP_GNUPLOT_SUPPORT
    //IndexHtmlRows gnuplotEntries{};
#endif
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_INDEX_HTML_HPP_
