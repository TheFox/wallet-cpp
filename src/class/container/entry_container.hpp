
#ifndef WALLETCPP_CONTAINER_ENTRY_CONTAINER_HPP_
#define WALLETCPP_CONTAINER_ENTRY_CONTAINER_HPP_

#include <string>
#include <utility> // pair
#include <map>
#include <cstdint> // uint8_t
#include <functional> // function

#include "class/entry.hpp"
#include "class/accountable.hpp"

namespace Wallet::Container
{
  // Types
  using EntryArray = std::vector<Entry>;

  using ContainerDay = std::uint8_t;
  using ContainerMonth = std::uint8_t;
  using ContainerYear = std::uint16_t;

  struct CategoryContainer final : public Accountable
  {
  };

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

  struct BaseEntryContainer : public Accountable
  {
    // Properties
    std::size_t dayCount{};
    std::size_t entryCount{};
  };

  struct DayEntryContainer final : public BaseEntryContainer
  {
    ContainerDay day{};
    EntryArray entries{};
  };

  using DayMap = std::map<ContainerDay, DayEntryContainer>;
  struct MonthEntryContainer final : public BaseEntryContainer, public BaseCategoryContainer
  {
    // Properties
    ContainerYear year{};
    DayMap days{};
    std::string fileName{};
    std::string yearMonth{};
  };

  using MonthMap = std::map<ContainerMonth, MonthEntryContainer>;
  using MonthPair = std::pair<ContainerMonth, MonthEntryContainer>;
  struct YearEntryContainer final : public BaseEntryContainer, public BaseCategoryContainer
  {
    // Properties
    ContainerYear year{};
    MonthMap months{};
  };

  using YearMap = std::map<ContainerYear, YearEntryContainer>;
  struct EntryContainer final : public BaseEntryContainer
  {
    YearMap years{};
  };
} // Wallet::Container Namespace

#endif // WALLETCPP_CONTAINER_ENTRY_CONTAINER_HPP_
