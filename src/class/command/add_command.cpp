
#ifdef DEBUG
#include <cstdio>
#endif

#include <iostream>

#include "add_command.hpp"
#include "../mutable_wallet.hpp"
#include "../entry.hpp"
#include "../../components.hpp"

namespace Wallet
{
  int AddCommand::execute()
  {
    using std::cout;
    using std::cin;
    using std::endl;

#ifdef DEBUG
    printf(" -> options %p\n", &this->options);
#endif

    Entry entry = this->options;

    if (this->options.isInteractively) {
      std::string _tmpStr{};

      cout << "Title: [" << entry.title << "] ";
      getline(cin, _tmpStr);
      cout << "Title: '" << _tmpStr << "'" << endl;
      if (!_tmpStr.empty()) {
        entry.title = _tmpStr;
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

      cout << "Category: [" << entry.category << "] ";
      getline(cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.category = _tmpStr;
      }

      cout << "Comment: [" << entry.comment << "] ";
      getline(cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.comment = _tmpStr;
      }
    }

    if (entry.title.empty()) {
      throw std::string{"Title is required for Add command."};
    }

    const bool isUnique = !this->options.isForced && !this->options.id.empty();

    // Inform User
    cout << "---------------" << endl;
    cout << "Wallet: " << this->options.walletPath << endl;
    cout << "File name: " << entry.getFileName() << endl;
    cout << "Is Unique: " << (isUnique ? "YES" : "NO") << endl;
    cout << "ID: " << entry.id << endl;
    cout << "---------------" << endl;
    cout << "Title: '" << entry.title << "'" << endl;
    cout << "Date: '" << entry.getDateStr() << "'" << endl;
    cout << "Revenue: " << entry.getRevenue() << endl;
    cout << "Expense: " << entry.getExpense() << endl;
    cout << "Balance: " << entry.getBalance() << endl;
    cout << "Category: '" << entry.category << "'" << endl;
    cout << "Comment: '" << entry.comment << "'" << endl;
    cout << "---------------" << endl;

    if (this->options.isInteractively) {
      cout << "OK? [Y/n] ";

      // Set terminal to raw mode.
      system("stty raw");

      // Read char.
      int input = getchar();

      // Reset terminal to normal "cooked" mode
      system("stty cooked");

      //printf("input: %d %d\n", input, '\r');

      cout << endl;
      if (input != 'Y' && input != 'y' && input != 13) {
        cout << "Aborted. Nothing done." << endl;
        return 0;
      }
      cout << "OK" << endl;
    }

    MutableWallet wallet{this->options.walletPath};
    wallet.setup();
    cout << "Try to add entry: " << entry.id << endl;
    const bool added = wallet.add(entry, isUnique);
    cout << "Added: " << (added ? "YES" : "NO") << endl;

    return Command::execute();
  }
} // Wallet Namespace