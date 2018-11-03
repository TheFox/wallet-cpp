
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

    // ID
    if (!this->commandOptions.id.empty()) {
      entry.setId(this->commandOptions.id);
    }

    // Title
    if (!this->commandOptions.id.empty()) {
      entry.setTitle(this->commandOptions.id);
    }

    // Date
    if (!this->commandOptions.date.empty()) {
      entry.setDate(this->commandOptions.date);
    }

    if (this->commandOptions.isInteractively) {
      // TODO
    }

    const bool isUnique = !this->commandOptions.isForced && !this->commandOptions.id.empty();

    // Inform User
    cout << "Wallet: " << this->commandOptions.walletPath << endl;
    cout << "ID: " << entry.getId() << endl;
    cout << "Title: " << entry.getTitle() << endl;
    cout << "Date: " << entry.getDate() << endl;
    cout << "File name: " << entry.getFileName() << endl;
    cout << "Is Unique: " << (isUnique ? "YES" : "NO") << endl;

    MutableWallet wallet{this->commandOptions.walletPath};
    wallet.setup();
    cout << "Try to add entry: " << entry.getId() << endl;
    const bool added = wallet.add(entry, isUnique);
    cout << "Added: " << (added ? "YES" : "NO") << endl;

    return Command::execute();
  }
} // Wallet Namespace
