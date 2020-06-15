
#ifndef WALLETCPP_HTML_MONTH_HTML_HPP_
#define WALLETCPP_HTML_MONTH_HTML_HPP_

#include <string>

#include "base_html.hpp"
#include "class/container/entry_container.hpp"
#include "class/container/epic_container.hpp"

namespace Wallet::Html
{
  using Container::Month;
  using Container::MonthPair;
  using Container::MonthEntryContainer;
  using Container::UnsortedEpics;
  using Container::UnsortedEpicPtrs;

  /**
   * Generates one month html file.
   */
  class MonthHtml final : public BaseHtml
  {
  public:
    //MonthHtml(fs::path, MonthPair, UnsortedEpics, const UnsortedEpicPtrs&);
    MonthHtml(fs::path, MonthPair, const UnsortedEpicPtrs&);
    void generate() const;
    const std::string name{};

  private:
    const MonthEntryContainer container{};
    const std::string year{};

    const UnsortedEpics epics{}; // @deprecated
    const UnsortedEpicPtrs& epicPtrs{};

    static std::string getMonthFile(Month) noexcept;
    static std::string getMonthName(Month) noexcept;
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_MONTH_HTML_HPP_
