
#ifndef WALLETCPP_FAKE_VERSION_COMMAND_HPP_
#define WALLETCPP_FAKE_VERSION_COMMAND_HPP_

#include "command.hpp"

namespace Wallet
{
  class FakeVersionCommand final : public Command
  {
  public:
    int execute() override;
  };
} // Wallet Namespace

#endif // WALLETCPP_FAKE_VERSION_COMMAND_HPP_
