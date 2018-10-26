
#ifdef DEBUG
#include <cstdio>
#endif
#include <iostream>

#include "add_command.hpp"
#include "wallet.hpp"
#include "entry.hpp"

namespace Wallet
{
  int AddCommand::execute()
  {
#ifdef DEBUG
    printf("Add '%d' '%s'\n", this->commandOptions.walletPath.has_value(), (*this->commandOptions.walletPath).c_str());
#endif
    using std::cout;
    using std::endl;

    Entry entry;

    if (this->commandOptions.isInteractively) {
    }

    Wallet wallet{this->commandOptions.walletPath};
    const bool added = wallet.add(entry, false);
    cout << "Added: " << (added ? "YES" : "NO") << endl;

    return Command::execute();
  }
}
