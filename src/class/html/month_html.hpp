
#ifndef WALLETCPP_HTML_MONTH_HTML_HPP_
#define WALLETCPP_HTML_MONTH_HTML_HPP_

#include <string>

#include "base_html.hpp"
#include "class/container/entry_container.hpp"

namespace Wallet::Html
{
  class MonthMustacheObject final : public BaseMustacheObject
  {
  public:
    // Constructor
    MonthMustacheObject(std::string, mstch::array, mstch::map, std::string, std::string, std::string);

  private:
    // Properties
    const std::string year{};
    const std::string month{};
    const std::string fileName{};

    // Functions
    mstch::node getYear() noexcept;
    mstch::node getMonth() noexcept;
    mstch::node getFileName() noexcept;
  };

  /**
   * Generates one month html file.
   */
  class MonthHtml final : public BaseHtml
  {
  public:
    MonthHtml(fs::path, Container::MonthPair);
    void generate() const;
    const std::string name{};

  private:
    const Container::MonthEntryContainer container{};
    const std::string year{};

    static std::string getMonthFile(Container::ContainerMonth) noexcept;
    static std::string getMonthName(Container::ContainerMonth) noexcept;
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_MONTH_HTML_HPP_
