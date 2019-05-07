
#ifndef WALLETCPP_COMMAND_OPTIONS_HPP_
#define WALLETCPP_COMMAND_OPTIONS_HPP_

#include <string>

#include "class/accountable.hpp"

namespace Wallet
{
  struct CommandOptions
  {
    // Wallet
    std::string walletPath = ".wallet";

    // Int to have different levels. Only two levels used so far.
    std::uint8_t verbose{0};

    // Entry
    std::string id{};
    std::string title{};
    std::string date{};
    Accountable::Number revenue{};
    Accountable::Number expense{};
    std::string category{};
    std::string comment{};
    std::string epic{};

    // HTML Command
    std::string path{};

    // Status
    bool isInteractively{};
    bool isForced{};
  };
} // Wallet Namespace

#endif // WALLETCPP_COMMAND_OPTIONS_HPP_
