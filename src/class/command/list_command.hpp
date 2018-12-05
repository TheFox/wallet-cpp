
#ifndef WALLETCPP_LIST_COMMAND_HPP_
#define WALLETCPP_LIST_COMMAND_HPP_

#include "command.hpp"
#include "../entry_container.hpp"

namespace Wallet
{
  class ListCommand final : public Command
  {
  public:
    int execute() override;
  };

  void listEntries(const Container::EntryContainer&);
} // Wallet Namespace

#endif // WALLETCPP_LIST_COMMAND_HPP_
