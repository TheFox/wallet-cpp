
#ifndef WALLETCPP_HTML_YEAR_HTML_HPP_
#define WALLETCPP_HTML_YEAR_HTML_HPP_

#include "base_html.hpp"
#include "class/container/entry_container.hpp"

namespace Wallet::Html
{
  class YearMustacheObject final : public BaseMustacheObject
  {
  public:
    // Constructor
    YearMustacheObject(std::string, mstch::array, mstch::map, std::string, Container::CategoryArray);

  private:
    // Properties
    const std::string year{};
    const Container::CategoryArray categoryNames{};

    // Functions
    mstch::node getYear() noexcept;
    mstch::node getCategoryCount() noexcept;
    mstch::node getCategories() noexcept;
  };

  /**
   * Generates one year html file.
   */
  class YearHtml final : public BaseHtml
  {
  public:
    YearHtml(fs::path, Wallet::Container::YearEntryContainer);
    void generate() const;

  private:
    const Wallet::Container::YearEntryContainer container{};
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_YEAR_HTML_HPP_
