
#include <cstdlib> // system
#include <iostream>
#include <istream> // getline
#include <iomanip> // setprecision
#include <ios> // fixed

#include "debug.hpp"
#include "add_command.hpp"
#include "components.hpp"
#include "class/mutable_wallet.hpp"
#include "class/entry.hpp"

namespace Wallet
{
  int AddCommand::execute()
  {
    //DLog(" -> options %p\n", &this->options);

    if (this->options.category.empty())
      this->options.category = "default";

    if (this->options.epic.empty())
      this->options.epic = "default";

    Entry entry{this->options};

    if (this->options.isInteractively) {
      std::string _tmpStr{};

      std::cout << "Title: [" << entry.title << "] ";
      std::getline(std::cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.title = _tmpStr;
      }

      std::cout << "Date: [" << entry.getDateStr() << "] ";
      std::getline(std::cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.setDate(_tmpStr);
      }

      std::cout << "Revenue: [" << std::fixed << std::setprecision(2) << entry.revenue << "] ";
      std::getline(std::cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.setRevenue(Components::stof(_tmpStr));
      }

      std::cout << "Expense: [" << std::fixed << std::setprecision(2) << entry.expense << "] ";
      std::getline(std::cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.setExpense(Components::stof(_tmpStr));
      }

      std::cout << "Category: [" << entry.category << "] ";
      std::getline(std::cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.category = _tmpStr;
      }

      std::cout << "Epic: [" << entry.epic << "] ";
      std::getline(std::cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.epic = _tmpStr;
      }

      std::cout << "Comment: [" << entry.comment << "] ";
      std::getline(std::cin, _tmpStr);
      if (!_tmpStr.empty()) {
        entry.comment = _tmpStr;
      }
    }

    if (entry.title.empty()) {
      throw std::string{"Title is required for Add command."};
    }

    const bool isUnique = !this->options.isForced && !this->options.id.empty();

    // Inform User
    std::cout << "---------------" << std::endl;
    std::cout << "Wallet: " << this->options.walletPath << std::endl;
    std::cout << "File name: " << entry.getFileName() << std::endl;
    std::cout << "Is Unique: " << (isUnique ? "YES" : "NO") << std::endl;
    std::cout << "ID: " << entry.id << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << "Title: '" << entry.title << "'" << std::endl;
    std::cout << "Date: '" << entry.getDateStr() << "'" << std::endl;
    std::cout << "Revenue: " << std::fixed << std::setprecision(2) << entry.revenue << std::endl;
    std::cout << "Expense: " << std::fixed << std::setprecision(2) << entry.expense << std::endl;
    std::cout << "Balance: " << std::fixed << std::setprecision(2) << entry.balance << std::endl;
    std::cout << "Category: '" << entry.category << "'" << std::endl;
    std::cout << "Comment: '" << entry.comment << "'" << std::endl;
    std::cout << "Epic Handle: '" << entry.epic << "'" << std::endl;
    std::cout << "---------------" << std::endl;

    if (this->options.isInteractively) {
      std::cout << "OK? [Y/n] ";

      // Set terminal to raw mode.
      std::system("stty raw");

      // Read char.
      int input = getchar();

      // Reset terminal to normal "cooked" mode
      std::system("stty cooked");

      std::cout << std::endl;
      if (input != 'Y' && input != 'y' && input != 13) {
        std::cout << "Aborted. Nothing done." << std::endl;
        return 0;
      }
      std::cout << "OK" << std::endl;
    }

    MutableWallet wallet{this->options.walletPath};
    std::cout << "Try to add entry: " << entry.id << std::endl;
    bool added{};
    if (isUnique)
      added = wallet.addUniqueEntry(entry);
    else
      added = wallet.addEntry(entry);
    std::cout << "Added: " << (added ? "YES" : "NO") << std::endl;

    if (added) {
      std::cout << "Check Epic '" << entry.epic << "'" << std::endl;

      if (!wallet.epicExists(entry.epic)) {
        std::cout << "Create new Epic '" << entry.epic << "'" << std::endl;

        Epic epic{};
        epic.handle = entry.epic;

        wallet.addEpic(epic);
      }
    }

    return Command::execute();
  }
} // Wallet Namespace
