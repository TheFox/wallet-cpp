
#include "html_command.hpp"
#include "immutable_wallet.hpp"
#include "entry.hpp"

namespace Wallet
{
  int HtmlCommand::execute()
  {
    Entry e;

    ImmutableWallet wallet{this->commandOptions.walletPath};
    wallet.setup();
    wallet.add(e, false);

    return Command::execute();
  }
} // Wallet Namespace
