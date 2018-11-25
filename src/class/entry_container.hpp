
#ifndef WALLETCPP_ENTRY_CONTAINER_HPP_
#define WALLETCPP_ENTRY_CONTAINER_HPP_

#include <string>
#include <map>

#include "entry.hpp"

namespace Wallet
{
  struct EntryContainer
  {
    // Types
    using EntryMap = std::map<std::string, std::vector<Entry>>;

    // Properties
    std::size_t dayCount;
    std::size_t entryCount;
    EntryMap entries;
  };
} // Wallet Namespace

#endif // WALLETCPP_ENTRY_CONTAINER_HPP_
