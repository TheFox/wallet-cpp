
#ifndef WALLETCPP_HTML_YEAR_HTML_HPP_
#define WALLETCPP_HTML_YEAR_HTML_HPP_

#include "base_html.hpp"
#include "../entry_container.hpp"

namespace Wallet::Html
{
  class YearHtml final : public BaseHtml
  {
  public:
    YearHtml(boost::filesystem::path, Wallet::Container::YearEntryContainer);
    void generate() const noexcept;

  private:
    const Wallet::Container::YearEntryContainer container{};
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_YEAR_HTML_HPP_
