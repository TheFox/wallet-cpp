
#ifndef WALLETCPP_ENTRY_CONTAINER_HPP_
#define WALLETCPP_ENTRY_CONTAINER_HPP_

#include <string>
#include <map>
#include <cstdint>

#include "entry.hpp"

namespace Wallet
{
  struct EntryContainer
  {
    // Types
    using EntryVec = std::vector<Entry>;
    using EntryMap = std::map<std::string, EntryVec>;
    using DayMap = std::map<std::uint8_t, EntryVec>;
    using MonthMap = std::map<std::uint8_t, DayMap>;
    using YearMap = std::map<std::uint16_t, MonthMap>;

    // Properties
    std::size_t dayCount{};
    std::size_t entryCount{};
    [[deprecated]] EntryMap entries{};
    YearMap years{};

    Entry::Number revenue{};
    Entry::Number expense{};
    Entry::Number balance{};
  };
} // Wallet Namespace

#endif // WALLETCPP_ENTRY_CONTAINER_HPP_
