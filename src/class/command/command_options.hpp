
#ifndef WALLETCPP_COMMAND_OPTIONS_HPP_
#define WALLETCPP_COMMAND_OPTIONS_HPP_

#include <string>

#include "class/trait/accountable.hpp"

namespace Wallet
{
  struct CommandOptions
  {
    // Wallet
    std::string walletPath = ".wallet";

    // Int to have different levels. Only two levels used so far.
    std::uint8_t verbose{0};

    // Common
    std::string date{};
    std::string category{};
    std::string epic{};

    // Entry
    std::string id{};
    std::string title{};
    Trait::Accountable::Number revenue{};
    Trait::Accountable::Number expense{};
    std::string comment{};

    // HTML Command
    std::string path{};

    // Epic Command
    std::string handle{};
    std::string bgColor{};

    // Status
    bool isInteractively{}; // Add Command
    bool isForced{}; // Add Command
    bool isRemove{}; // Epic Command
  };
} // Wallet Namespace

#endif // WALLETCPP_COMMAND_OPTIONS_HPP_
