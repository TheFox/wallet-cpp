
#ifndef WALLETCPP_COMMAND_OPTIONS_HPP_
#define WALLETCPP_COMMAND_OPTIONS_HPP_

#include <string>
#include <cmath>

#ifdef __has_include
#  if __has_include(<optional>)
#    include <optional>
#  elif __has_include(<experimental/optional>)
#    include <experimental/optional>
#  elif __has_include(<boost/optional.hpp>)
#    include <boost/optional.hpp>
#  else
#    error "Missing <optional>"
#  endif
#endif

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
    // std::optional<std::string> path{};
    std::string path{};

    // Status
    bool isInteractively{};
    bool isForced{};
  };
} // Wallet Namespace

#endif // WALLETCPP_COMMAND_OPTIONS_HPP_
