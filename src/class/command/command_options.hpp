
#ifndef WALLETCPP_COMMAND_OPTIONS_HPP_
#define WALLETCPP_COMMAND_OPTIONS_HPP_

#include <string>
#include <cmath>

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
    std::float_t revenue{};
    std::float_t expense{};
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
