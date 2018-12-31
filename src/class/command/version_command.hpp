
#ifndef WALLETCPP_VERSION_COMMAND_HPP_
#define WALLETCPP_VERSION_COMMAND_HPP_

#include "command.hpp"

namespace Wallet
{
  class VersionCommand final : public Command
  {
  public:
    int execute() override;
  };
} // Wallet Namespace

#endif // WALLETCPP_VERSION_COMMAND_HPP_
