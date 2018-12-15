
#ifndef WALLETCPP_HTML_YEAR_HTML_HPP_
#define WALLETCPP_HTML_YEAR_HTML_HPP_

#include "base_html.hpp"
#include "../entry_container.hpp"

namespace Wallet::Html
{
  class YearHtml final : public BaseHtml
  {
  public:
    YearHtml(fs::path, Wallet::Container::YearEntryContainer);
    void generate();

  private:
    const Wallet::Container::EntryContainer xcontainer{};
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_YEAR_HTML_HPP_
