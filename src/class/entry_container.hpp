
#ifndef WALLETCPP_ENTRY_CONTAINER_HPP_
#define WALLETCPP_ENTRY_CONTAINER_HPP_

#include <map>
#include <cstdint>

#include "entry.hpp"
#include "account_able.hpp"

namespace Wallet::Container
{
  // Types
  using EntryVec = std::vector<Entry>;

  using ContainerDay = std::uint8_t;
  using ContainerMonth = std::uint8_t;
  using ContainerYear = std::uint16_t;

  struct BaseEntryContainer : public AccountAble
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
  struct MonthEntryContainer final : public BaseEntryContainer
  {
    ContainerMonth month{};
    DayMap days{};
  };

  using MonthMap = std::map<ContainerMonth, MonthEntryContainer>;
  using MonthPair = std::pair<ContainerMonth, MonthEntryContainer>;
  struct YearEntryContainer final : public BaseEntryContainer
  {
    ContainerYear year{};
    MonthMap months{};
  };

  using YearMap = std::map<ContainerYear, YearEntryContainer>;
  struct EntryContainer final : public BaseEntryContainer
  {
    YearMap years{};
  };
} // Wallet::Container Namespace

#endif // WALLETCPP_ENTRY_CONTAINER_HPP_
