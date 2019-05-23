
#ifndef WALLETCPP_CONTAINER_ENTRY_CONTAINER_HPP_
#define WALLETCPP_CONTAINER_ENTRY_CONTAINER_HPP_

#include <string>
#include <utility> // pair
#include <map>
#include <cstdint> // uint8_t
#include <functional> // function

#include "class/entry.hpp"
#include "class/epic.hpp"
#include "class/trait/accountable.hpp"
#include "epic_container.hpp"

namespace Wallet::Container
{
  // Types
  using UnsortedEntries = std::vector<Entry>;

  using Day = std::uint8_t;
  using Month = std::uint8_t;
  using Year = std::uint16_t;

  struct CategoryContainer final : public Wallet::Trait::Accountable
  {
    std::string category{"default"};
    bool isDefaultCategory{true};
  };

  /**
   * Compare Categories by name.
   */
  class CategoryComparator
  {
  public:
    bool operator()(const std::string&, const std::string&) const;
  };

  using UnsortedCategories = std::vector<std::string>;
  using SortedCategories = std::map<std::string, CategoryContainer, CategoryComparator>;
  struct BaseCategoryContainer
  {
    BaseCategoryContainer();

    // Properties
    SortedCategories categories{};
  };

  struct BaseEntryContainer : public Wallet::Trait::Accountable
  {
    // Properties
    std::size_t dayCount{};
    std::size_t entryCount{};
  };

  struct DayEntryContainer final : public BaseEntryContainer
  {
    Day day{};
    UnsortedEntries entries{};
  };

  using DayMap = std::map<Day, DayEntryContainer>;
  struct MonthEntryContainer final : public BaseEntryContainer, public BaseCategoryContainer, public BaseEpicContainer
  {
    // Properties
    Year year{};
    DayMap days{};
    std::string fileName{};
    std::string yearMonth{};
  };

  using MonthMap = std::map<Month, MonthEntryContainer>;
  using MonthPair = std::pair<Month, MonthEntryContainer>;
  struct YearEntryContainer final : public BaseEntryContainer, public BaseCategoryContainer, public BaseEpicContainer
  {
    // Properties
    Year year{};
    MonthMap months{};
  };

  using YearMap = std::map<Year, YearEntryContainer>;
  struct EntryContainer final : public BaseEntryContainer, public BaseCategoryContainer, public BaseEpicContainer
  {
    YearMap years{};
  };
} // Wallet::Container Namespace

#endif // WALLETCPP_CONTAINER_ENTRY_CONTAINER_HPP_
