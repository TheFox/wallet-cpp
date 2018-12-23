
#ifndef WALLETCPP_ENTRY_CONTAINER_HPP_
#define WALLETCPP_ENTRY_CONTAINER_HPP_

#include <map>
#include <cstdint>

#include "class/entry.hpp"
#include "class/accountable.hpp"

namespace Wallet::Container
{
  // Types
  using EntryVec = std::vector<Entry>;

  using ContainerDay = std::uint8_t;
  using ContainerMonth = std::uint8_t;
  using ContainerYear = std::uint16_t;

  struct CategoryContainer final : public Accountable
  {
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
    EntryVec entries{};
  };

  using DayMap = std::map<ContainerDay, DayEntryContainer>;
  using CategoryMap = std::map<std::string, CategoryContainer>;
  struct MonthEntryContainer final : public BaseEntryContainer
  {
    ContainerYear year{};
    ContainerMonth month{};
    DayMap days{};
    CategoryMap categories{};
  };

  using MonthMap = std::map<ContainerMonth, MonthEntryContainer>;
  using MonthPair = std::pair<ContainerMonth, MonthEntryContainer>;
  struct YearEntryContainer final : public BaseEntryContainer
  {
    ContainerYear year{};
    MonthMap months{};
    CategoryMap categories{};
  };

  using YearMap = std::map<ContainerYear, YearEntryContainer>;
  struct EntryContainer final : public BaseEntryContainer
  {
    YearMap years{};
  };
} // Wallet::Container Namespace

#endif // WALLETCPP_ENTRY_CONTAINER_HPP_
