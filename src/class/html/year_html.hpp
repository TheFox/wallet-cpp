
#ifndef WALLETCPP_HTML_YEAR_HTML_HPP_
#define WALLETCPP_HTML_YEAR_HTML_HPP_

#include "base_html.hpp"
#include "class/container/entry_container.hpp"

namespace Wallet::Html
{
  /**
   * Generates one year html file.
   */
  class YearHtml final : public BaseHtml
  {
  public:
    YearHtml(fs::path, fs::path, Container::YearEntryContainer);
    void generate() const;

  private:
    const Container::YearEntryContainer container{};
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_YEAR_HTML_HPP_
