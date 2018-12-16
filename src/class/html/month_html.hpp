
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
    MonthHtml(boost::filesystem::path, Container::MonthPair);
    void generate() const noexcept;
    const std::string name{};

  private:
    const Container::MonthEntryContainer container{};
    const std::string year{};

    static std::string getMonthFile(Container::ContainerMonth) noexcept;
    static std::string getMonthName(Container::ContainerMonth) noexcept;
  };
}

#endif // WALLETCPP_HTML_MONTH_HTML_HPP_
