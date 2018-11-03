
#ifndef WALLETCPP_COMMAND_OPTIONS_HPP_
#define WALLETCPP_COMMAND_OPTIONS_HPP_

#include <string>
#include <cmath>

namespace Wallet
{
  struct CommandOptions
  {
    std::string walletPath = ".wallet";
    std::string id{};
    std::string title{};
    std::string date{};
    std::float_t revenue{};
    std::float_t expense{};
    std::string category{};
    std::string comment{};

    // Status
    bool isInteractively{};
    bool isForced{};
  };
} // Wallet Namespace

#endif // WALLETCPP_COMMAND_OPTIONS_HPP_
