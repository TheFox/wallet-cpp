
#ifdef DEBUG
#include <cstdio>
#endif

#include "list_command.hpp"
#include "../immutable_wallet.hpp"

namespace Wallet
{
  int ListCommand::execute()
  {
    ImmutableWallet wallet{this->options.walletPath};
    wallet.setup();

    const auto entries = wallet.getEntries();

    listEntries(entries);

    return Command::execute();
  }

  void listEntries(const MutableWallet::EntryMap& entries){
#ifdef DEBUG
    printf(" -> listEntries()\n");
#endif
  }
} // Wallet Namespace
