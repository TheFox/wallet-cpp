
#ifndef WALLETCPP_HTML_MONTH_HTML_HPP_
#define WALLETCPP_HTML_MONTH_HTML_HPP_

#include <string>

#include "base_html.hpp"
#include "../entry_container.hpp"

namespace Wallet::Html
{
  class MonthHtml final : public BaseHtml
  {
  public:
    MonthHtml(std::string, fs::path, Wallet::Container::MonthEntryContainer);
    void generate() const noexcept;

  private:
    const std::string name;
    const fs::path basePath{};
    const Wallet::Container::MonthEntryContainer container{};
  };
}

#endif // WALLETCPP_HTML_MONTH_HTML_HPP_
