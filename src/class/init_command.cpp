
#include "init_command.hpp"
#include "mutable_wallet.hpp"

namespace Wallet
{
  int InitCommand::execute()
  {
    MutableWallet wallet{this->commandOptions.walletPath};
    wallet.setup(true);

    return Command::execute();
  }
} // Wallet Namespace
