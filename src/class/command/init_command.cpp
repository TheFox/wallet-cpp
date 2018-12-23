
#include "init_command.hpp"
#include "class/mutable_wallet.hpp"

namespace Wallet
{
  int InitCommand::execute()
  {
    MutableWallet wallet{this->options.walletPath};
    wallet.setup(true);

    return Command::execute();
  }
} // Wallet Namespace
