
#include "html_command.hpp"
#include "class/immutable_wallet.hpp"

namespace Wallet
{
  int HtmlCommand::execute()
  {
    ImmutableWallet wallet{this->options.walletPath};
    wallet.setup();

    wallet.htmlOutput(this->options.path);

    return Command::execute();
  }
} // Wallet Namespace
