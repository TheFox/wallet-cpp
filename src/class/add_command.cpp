
#ifdef DEBUG
#include <cstdio>
#endif

#include <iostream>

#include "add_command.hpp"
#include "mutable_wallet.hpp"
#include "entry.hpp"
#include "components.hpp"

namespace Wallet
{
  int AddCommand::execute()
  {
    using std::cout;
    using std::cin;
    using std::endl;
    using Components::stof;

#ifdef DEBUG
    printf(" -> commandOptions %p\n", &this->commandOptions);
#endif

    Entry entry = this->commandOptions;

    if (this->commandOptions.isInteractively) {
      std::string _tmpStr{};

      cout << "Title: [" << entry.getTitle() << "] ";
      getline(cin, _tmpStr);
      cout << "Title: '" << _tmpStr << "'" << endl;
      if (!_tmpStr.empty()) {
        entry.setTitle(_tmpStr);
      }

      cout << "Date: [" << entry.getDateStr() << "] ";
      getline(cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.setDate(_tmpStr);
      }

      cout << "Revenue: [" << entry.getRevenue() << "] ";
      getline(cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.setRevenue(Components::stof(_tmpStr));
      }

      cout << "Expense: [" << entry.getExpense() << "] ";
      getline(cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.setExpense(Components::stof(_tmpStr));
      }

      // Balance
      entry.calcBalance();

      cout << "Category: [" << entry.getCategory() << "] ";
      getline(cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.setCategory(_tmpStr);
      }

      cout << "Comment: [" << entry.getComment() << "] ";
      getline(cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.setComment(_tmpStr);
      }
    }

    if (entry.getTitle().empty()) {
      throw std::string{"Title is required for Add command."};
    }

    const bool isUnique = !this->commandOptions.isForced && !this->commandOptions.id.empty();

    // Inform User
    cout << "---------------" << endl;
    cout << "Wallet: " << this->commandOptions.walletPath << endl;
    cout << "File name: " << entry.getFileName() << endl;
    cout << "Is Unique: " << (isUnique ? "YES" : "NO") << endl;
    cout << "ID: " << entry.getId() << endl;
    cout << "---------------" << endl;
    cout << "Title: '" << entry.getTitle() << "'" << endl;
    cout << "Date: '" << entry.getDateStr() << "'" << endl;
    cout << "Revenue: " << entry.getRevenue() << endl;
    cout << "Expense: " << entry.getExpense() << endl;
    cout << "Balance: " << entry.getBalance() << endl;
    cout << "Category: '" << entry.getCategory() << "'" << endl;
    cout << "Comment: '" << entry.getComment() << "'" << endl;
    cout << "---------------" << endl;

    if (this->commandOptions.isInteractively) {
      cout << "OK? [Y/n] ";

      // Set terminal to raw mode.
      system("stty raw");

      // Read char.
      int input = getchar();

      // Reset terminal to normal "cooked" mode
      system("stty cooked");

      //printf("input: %d %d\n", input, '\r');

      cout << endl;
      if (input != 'Y' && input != 'y') {
        cout << "Aborted. Nothing done." << endl;
        return 0;
      }
      cout << "OK" << endl;
    }

    MutableWallet wallet{this->commandOptions.walletPath};
    wallet.setup();
    cout << "Try to add entry: " << entry.getId() << endl;
    const bool added = wallet.add(entry, isUnique);
    cout << "Added: " << (added ? "YES" : "NO") << endl;

    return Command::execute();
  }
} // Wallet Namespace
