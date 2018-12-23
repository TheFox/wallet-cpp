
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

    // Entry
    std::string id{};
    std::string title{};
    std::string date{};
    Accountable::Number revenue{};
    Accountable::Number expense{};
    std::string category{"default"};
    std::string comment{};

    // HTML Command
    std::string path{};

    // Status
    bool isInteractively{};
    bool isForced{};
  };
} // Wallet Namespace

#endif // WALLETCPP_COMMAND_OPTIONS_HPP_
