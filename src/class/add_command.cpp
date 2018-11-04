
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

#ifdef DEBUG
    printf(" -> commandOptions %p\n", &this->commandOptions);
#endif
    if (this->commandOptions.title.empty()) {
      throw std::string{"Title is required for Add command."};
    }

    Entry entry = this->commandOptions;

    if (this->commandOptions.isInteractively) {
      // TODO
    }

    const bool isUnique = !this->commandOptions.isForced && !this->commandOptions.id.empty();

    // Inform User
    cout << "Wallet: " << this->commandOptions.walletPath << endl;
    cout << "ID: " << entry.getId() << endl;
    cout << "Title: " << entry.getTitle() << endl;
    cout << "Date: " << entry.getDateStr() << endl;
    cout << "Revenue: " << entry.getRevenue() << endl;
    cout << "Expense: " << entry.getExpense() << endl;
    cout << "Balance: " << entry.getBalance() << endl;
    cout << "Category: " << entry.getCategory() << endl;
    cout << "Comment: " << entry.getComment() << endl;
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
