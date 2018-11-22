
#ifndef WALLETCPP_HELP_COMMAND_HPP_
#define WALLETCPP_HELP_COMMAND_HPP_

#include "command.hpp"

namespace Wallet
{
  class HelpCommand final : public Command
  {
  public:
    int execute() override;
  };
} // Wallet Namespace

#endif // WALLETCPP_HELP_COMMAND_HPP_
