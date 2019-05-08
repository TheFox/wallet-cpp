
#include <sstream>
#include <iomanip> // setprecision
#include <ios> // fixed, left, right
#include <cstddef> // size_t

#include "debug.hpp"
#include "list_command.hpp"
#include "components.hpp"
#include "class/mutable_wallet.hpp"
#include "class/entry.hpp"

namespace Wallet
{
  int ListCommand::execute()
  {
    const MutableWallet wallet{this->options.walletPath};

    const auto date = Components::parseDate(this->options.date);
    listEntries(wallet.getEntries(date, this->options.category, this->options.epic));

    return Command::execute();
  }

  void listEntries(const Container::EntryContainer& container)
  {
    DLog(" -> listEntries() c=%lu\n", container.entryCount);

    if (container.entryCount == 0) {
      std::cout << "No entries found." << std::endl;
      return;
    }

    auto _countLen = std::log10(container.entryCount) + 1;
    auto countLenSize = static_cast<const std::size_t>(_countLen);
    auto countLenInt = static_cast<const int>(countLenSize);

    // Header
    std::cout
      << std::string(countLenSize, '#')
      << " Date          Revenue    Expense    Balance   Title"
      << std::endl;

    // Entries
    std::size_t count{0};
    for (const auto& yearPair : container.years) {
      for (const auto& monthPair : yearPair.second.months)
      for (const auto& dayPair : monthPair.second.days)
      for (const auto& entry : dayPair.second.entries) {
        ++count;

        // Print Entry
        std::cout
          << std::setw(countLenInt) << std::left << count
          << ' ' << entry.getDateStr()
          << ' ' << std::setw(10) << std::right << entry.getRevenueStr()
          << ' ' << std::setw(10) << std::right << entry.getExpenseStr()
          << ' ' << std::setw(10) << std::right << entry.getBalanceStr()
          << "   " << entry.title
          << std::endl;
      }
    }

    // Total
    std::cout
      << std::endl
      << std::string(countLenSize, ' ')
      << "           "
      << ' ' << std::setw(10) << std::right << std::fixed << std::setprecision(2) << container.revenue
      << ' ' << std::setw(10) << std::right << std::fixed << std::setprecision(2) << container.expense
      << ' ' << std::setw(10) << std::right << std::fixed << std::setprecision(2) << container.balance
      << "   TOTAL"
      << std::endl;
  }
} // Wallet Namespace
