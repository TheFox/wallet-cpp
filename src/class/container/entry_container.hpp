
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
  using EntryArray = std::vector<Entry>;

  using ContainerDay = std::uint8_t;
  using ContainerMonth = std::uint8_t;
  using ContainerYear = std::uint16_t;

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

  using CategoryArray = std::vector<std::string>;
  using CategoryMap = std::map<std::string, CategoryContainer, CategoryComparator>;
  struct BaseCategoryContainer
  {
    BaseCategoryContainer();

    // Properties
    CategoryMap categories{};
  };

  struct BaseEntryContainer : public Wallet::Trait::Accountable
  {
    // Properties
    std::size_t dayCount{};
    std::size_t entryCount{};
    //std::size_t categoryCount{};
    //std::size_t epicCount{};
  };

  struct DayEntryContainer final : public BaseEntryContainer
  {
    ContainerDay day{};
    EntryArray entries{};
  };

  using DayMap = std::map<ContainerDay, DayEntryContainer>;
  struct MonthEntryContainer final : public BaseEntryContainer, public BaseCategoryContainer, public BaseEpicContainer
  {
    // Properties
    ContainerYear year{};
    DayMap days{};
    std::string fileName{};
    std::string yearMonth{};
  };

  using MonthMap = std::map<ContainerMonth, MonthEntryContainer>;
  using MonthPair = std::pair<ContainerMonth, MonthEntryContainer>;
  struct YearEntryContainer final : public BaseEntryContainer, public BaseCategoryContainer, public BaseEpicContainer
  {
    // Properties
    ContainerYear year{};
    MonthMap months{};
  };

  using YearMap = std::map<ContainerYear, YearEntryContainer>;
  struct EntryContainer final : public BaseEntryContainer, public BaseCategoryContainer, public BaseEpicContainer
  {
    YearMap years{};
  };
} // Wallet::Container Namespace

#endif // WALLETCPP_CONTAINER_ENTRY_CONTAINER_HPP_
