
#ifndef WALLETCPP_ENTRY_CONTAINER_HPP_
#define WALLETCPP_ENTRY_CONTAINER_HPP_

#include <string>
#include <map>
#include <cstdint>

#include "entry.hpp"

namespace Wallet::Container
{
  // Types
  using EntryVec = std::vector<Entry>;

  using ContainerDay = std::uint8_t;
  using ContainerMonth = std::uint8_t;
  using ContainerYear = std::uint16_t;

  struct BaseEntryContainer
  {
    // Properties
    std::size_t dayCount{};
    std::size_t entryCount{};

    Entry::Number revenue{};
    Entry::Number expense{};
    Entry::Number balance{};
  };

  struct DayEntryContainer : BaseEntryContainer
  {
    ContainerDay day{};
    EntryVec entries{};
  };

  using DayMap = std::map<ContainerDay, DayEntryContainer>;
  struct MonthEntryContainer : BaseEntryContainer
  {
    ContainerMonth month{};
    DayMap days{};
  };

  using MonthMap = std::map<ContainerMonth, MonthEntryContainer>;
  struct YearEntryContainer : BaseEntryContainer
  {
    ContainerYear year{};
    MonthMap months{};
  };

  using YearMap = std::map<ContainerYear, YearEntryContainer>;
  struct EntryContainer : BaseEntryContainer
  {
    YearMap years{};
  };
} // Wallet::Container Namespace

#endif // WALLETCPP_ENTRY_CONTAINER_HPP_
