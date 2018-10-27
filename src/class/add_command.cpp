
#ifdef DEBUG
#include <cstdio>
#endif
#include <iostream>

#include "add_command.hpp"
#include "mutable_wallet.hpp"
#include "entry.hpp"

namespace Wallet
{
  int AddCommand::execute()
  {
    using std::cout;
    using std::endl;

    Entry entry;

    if (this->commandOptions.isInteractively) {
    }

    MutableWallet wallet{this->commandOptions.walletPath};
    wallet.setup();
    const bool added = wallet.add(entry, false);
    cout << "Added: " << (added ? "YES" : "NO") << endl;

    return Command::execute();
  }
} // Wallet Namespace
