
#ifndef WALLETCPP_LIST_COMMAND_HPP_
#define WALLETCPP_LIST_COMMAND_HPP_

#include "command.hpp"
#include "../mutable_wallet.hpp"

namespace Wallet
{
  class ListCommand final : public Command
  {
  public:
    int execute() override;
  };

  void listEntries(const MutableWallet::EntryMap&);
} // Wallet Namespace

#endif // WALLETCPP_LIST_COMMAND_HPP_
