
#ifndef WALLETCPP_INIT_COMMAND_HPP_
#define WALLETCPP_INIT_COMMAND_HPP_

#include "command.hpp"

namespace Wallet
{
  class InitCommand final : public Command
  {
  public:
    int execute() override;
  };
} // Wallet Namespace

#endif // WALLETCPP_INIT_COMMAND_HPP_
