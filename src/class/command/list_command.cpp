
#ifdef DEBUG
#include <cstdio>
#endif

#include "list_command.hpp"
#include "../immutable_wallet.hpp"

namespace Wallet
{
  int ListCommand::execute()
  {
    ImmutableWallet wallet{this->options.walletPath};
    wallet.setup();

    const auto entries = wallet.getEntries();

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
      << " Date          Revenue    Expense    Balance"
      << endl;

    // Entries
    u_int count{0};
    for (const auto& dayPair : container.entries) {
      //cout << "day" << endl;

      for (const auto& entry : dayPair.second) {
        ++count;

        // Entry
        cout
          << setw(countLenInt) << left << count
          << ' ' << entry.getDateStr()
          << ' ' << setw(10) << right << entry.getRevenue()
          << ' ' << setw(10) << right << entry.getExpense()
          << ' ' << setw(10) << right << entry.getBalance()
          << endl;
      }
    }
  }
} // Wallet Namespace
