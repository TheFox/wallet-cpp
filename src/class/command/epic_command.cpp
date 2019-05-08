
#include "debug.hpp"
#include "epic_command.hpp"
#include "class/epic.hpp"
#include "class/mutable_wallet.hpp"

namespace Wallet
{
  int EpicCommand::execute()
  {
    DLog(" -> EpicCommand::execute()");

    MutableWallet wallet{this->options.walletPath};
    wallet.logLevel = this->options.verbose;

    wallet.epicExists("e1");

    Epic e1{};
    e1.id = "id1";
    e1.handle = "e1";
    e1.name = "My Epic1";
    wallet.addEpic(e1);

    return Command::execute();
  }
} // Wallet Namespace
