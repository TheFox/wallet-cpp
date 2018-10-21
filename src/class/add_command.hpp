
#ifndef WALLET_ADD_COMMAND_HPP_
#define WALLET_ADD_COMMAND_HPP_

#include "command.hpp"

namespace Wallet
{
  class AddCommand final : public Command
  {
  public:
    int execute() override;
  };
}

#endif // WALLET_ADD_COMMAND_HPP_
