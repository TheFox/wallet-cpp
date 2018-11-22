
#ifndef WALLETCPP_LIST_COMMAND_HPP_
#define WALLETCPP_LIST_COMMAND_HPP_

#include "command.hpp"

namespace Wallet
{
  class ListCommand final : public Command
  {
  public:
    int execute() override;
  };
} // Wallet Namespace

#endif // WALLETCPP_LIST_COMMAND_HPP_
