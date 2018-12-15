
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
    void generate() const noexcept;

  private:
    const fs::path basePath{};
    const Wallet::Container::YearEntryContainer container{};
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_YEAR_HTML_HPP_
