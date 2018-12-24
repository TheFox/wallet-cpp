
#ifndef WALLETCPP_HTML_YEAR_HTML_HPP_
#define WALLETCPP_HTML_YEAR_HTML_HPP_

#include "base_html.hpp"
#include "class/container/entry_container.hpp"

#ifdef DEBUG
#define WALLETCPP_YEAR_VIEW_PATH "./resources/views/year.mustache"
#else
#define WALLETCPP_YEAR_VIEW_PATH PROJECT_SHARE_RESOURCES_DIR "/views/year.mustache"
#endif

namespace Wallet::Html
{
  class YearMustacheObject final : public BaseMustacheObject
  {
  public:
    // Constructor
    YearMustacheObject(std::string, mstch::array, mstch::map, std::string);

  private:
    // Properties
    const std::string year{};

    // Functions
    mstch::node getYear() noexcept;
    mstch::node getCategoryCount() noexcept;
  };

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
