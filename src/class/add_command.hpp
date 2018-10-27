
#ifndef WALLETCPP_ADD_COMMAND_HPP_
#define WALLETCPP_ADD_COMMAND_HPP_

#include "command.hpp"

namespace Wallet
{
  class AddCommand final : public Command
  {
  public:
    int execute() override;
  };
} // Wallet Namespace

#endif // WALLETCPP_ADD_COMMAND_HPP_
