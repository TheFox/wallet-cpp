
#ifdef DEBUG
#include <cstdio>
#endif

#include <sstream>

#include "list_command.hpp"
#include "../immutable_wallet.hpp"
#include "../../components.hpp"

namespace Wallet
{
  int ListCommand::execute()
  {
    ImmutableWallet wallet{this->options.walletPath};
    wallet.setup();

    EntryContainer entries{};

    auto date = Components::parseDate(this->options.date);
    if (0 == date.year && 0 == date.month && 0 == date.day) {
      entries = wallet.getEntries();
    }
    else if (0 != date.year && 0 == date.month && 0 == date.day) {
      // YYYY
      entries = wallet.getEntries(date.year);
    }
    else if (0 != date.year && 0 != date.month && 0 == date.day) {
      // YYYY-MM
      entries = wallet.getEntries(date.year, date.month);
    }
    else {
      // YYYY-MM-DD (and MM-DD and DD)
      entries = wallet.getEntries(date.year, date.month, date.day);
    }

    listEntries(entries);

    return Command::execute();
  }

  void listEntries(const EntryContainer& container)
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

    auto _countLen = std::log10(container.entryCount) + 1;
    auto countLenSize = static_cast<const std::size_t>(_countLen);
    auto countLenInt = static_cast<const int>(countLenSize);

    // Header
    cout
      << string(countLenSize, '#')
      << " Date          Revenue    Expense    Balance   Title"
      << endl;

    // Entries
    u_int count{0};
    for (const auto& dayPair : container.entries) {
      for (const auto& entry : dayPair.second) {
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
  }
} // Wallet Namespace
