
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
    entry.setId("id1");

    if (this->commandOptions.isInteractively) {
    }

    bool isUnique = false;

    MutableWallet wallet{this->commandOptions.walletPath};
    wallet.setup();
    cout << "Try to add entry: " << entry.getId() << endl;
    const bool added = wallet.add(entry, isUnique);
    cout << "Added: " << (added ? "YES" : "NO") << endl;

    return Command::execute();
  }
} // Wallet Namespace
