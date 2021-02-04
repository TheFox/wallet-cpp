
#ifndef WALLETCPP_MUSTACHE_YEAR_MUSTACHE_HPP_
#define WALLETCPP_MUSTACHE_YEAR_MUSTACHE_HPP_

#include <string>

#include "base_mustache.hpp"
#include "class/container/entry_container.hpp"
#include "class/container/epic_container.hpp"

namespace Wallet::Mustache
{
  using Container::UnsortedCategories;
  using Container::SortedEpicPtrs;

  // TODO: rename to YearView
  class YearMustache final : public BaseMustache
  {
  public:
    // Constructor
    YearMustache(std::string, mstch::array, mstch::map, std::string, UnsortedCategories, SortedEpicPtrs, std::string);

  private:
    // Properties
    const std::string year{};
    const UnsortedCategories categoryNames{};
    const SortedEpicPtrs epicPtrs{};
    const std::string pngFileName{};

    // Functions
    mstch::node getYear() noexcept;
    mstch::node getCategoryCount() noexcept;
    mstch::node getCategories() noexcept;
    mstch::node getEpicCount() noexcept;
    mstch::node getEpics() noexcept;
    mstch::node getHasEpics() noexcept;
    mstch::node getPngFileName() noexcept;
  };
} // Wallet::Mustache Namespace

#endif // WALLETCPP_MUSTACHE_YEAR_MUSTACHE_HPP_
