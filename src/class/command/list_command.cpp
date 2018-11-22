
#include "list_command.hpp"
#include "../immutable_wallet.hpp"

namespace Wallet
{
  int ListCommand::execute()
  {
    ImmutableWallet wallet{this->options.walletPath};
    wallet.setup();

    return Command::execute();
  }
} // Wallet Namespace
