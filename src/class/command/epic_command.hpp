
#ifndef WALLETCPP_EPIC_COMMAND_HPP_
#define WALLETCPP_EPIC_COMMAND_HPP_

#include "command.hpp"

namespace Wallet
{
  class EpicCommand final : public Command
  {
  public:
    int execute() override;
  };
} // Wallet Namespace

#endif // WALLETCPP_EPIC_COMMAND_HPP_
