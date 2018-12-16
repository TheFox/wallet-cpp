
#ifdef DEBUG
#include <cstdio>
#endif

#include <sstream>
#include <iomanip> // setprecision
#include <ios> // fixed
#include <cstddef>

#include "list_command.hpp"
#include "../immutable_wallet.hpp"
#include "../entry.hpp"
#include "../../components.hpp"

namespace Wallet
{
  int ListCommand::execute()
  {
    ImmutableWallet wallet{this->options.walletPath};
    wallet.setup();

    const auto date = Components::parseDate(this->options.date);
    listEntries(wallet.getEntries(date));

    return Command::execute();
  }

  void listEntries(const Container::EntryContainer& container)
  {
    using std::string;
    using std::cout;
    using std::endl;
    using std::setw;
    using std::right;
    using std::left;

#ifdef DEBUG
    printf(" -> listEntries() c=%lu\n", container.entryCount);
#endif

    if (container.entryCount == 0) {
      cout << "No entries found." << endl;
      return;
    }

    auto _countLen = std::log10(container.entryCount) + 1;
    auto countLenSize = static_cast<const std::size_t>(_countLen);
    auto countLenInt = static_cast<const int>(countLenSize);

    // Header
    cout
      << string(countLenSize, '#')
      << " Date          Revenue    Expense    Balance   Title"
      << endl;

    // Entries
    std::size_t count{0};
    for (const auto& yearPair : container.years) {
      for (const auto& monthPair : yearPair.second.months)
      for (const auto& dayPair : monthPair.second.days)
      for (const auto& entry : dayPair.second.entries) {
        ++count;

        // Print Entry
        cout
          << setw(countLenInt) << left << count
          << ' ' << entry.getDateStr()
          << ' ' << setw(10) << right << entry.getRevenueStr()
          << ' ' << setw(10) << right << entry.getExpenseStr()
          << ' ' << setw(10) << right << entry.getBalanceStr()
          << "   " << entry.title
          << endl;
      }
    }

    // Total
    cout
      << endl
      << string(countLenSize, ' ')
      << "           "
      << ' ' << setw(10) << right << std::fixed << std::setprecision(2) << container.revenue
      << ' ' << setw(10) << right << std::fixed << std::setprecision(2) << container.expense
      << ' ' << setw(10) << right << std::fixed << std::setprecision(2) << container.balance
      << "   TOTAL"
      << endl;
  }
} // Wallet Namespace
