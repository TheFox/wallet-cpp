
#include "html_command.hpp"
#include "../immutable_wallet.hpp"

namespace Wallet
{
  int HtmlCommand::execute()
  {
    ImmutableWallet wallet{this->options.walletPath};
    wallet.setup();

    return Command::execute();
  }
} // Wallet Namespace
