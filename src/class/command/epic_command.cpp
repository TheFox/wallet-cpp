
#include "debug.hpp"
#include "epic_command.hpp"
#include "class/epic.hpp"
#include "class/mutable_wallet.hpp"

namespace Wallet
{
  int EpicCommand::execute()
  {
    DLog(" -> EpicCommand::execute()\n");

    MutableWallet wallet{this->options.walletPath};
    wallet.logLevel = this->options.verbose;

    try {
      const auto epic = wallet.getEpicByHandle("e1");
      DLog(" -> EpicCommand::execute() -> found epic: '%s'\n", epic.handle.c_str());
    }
    catch (const std::string& e) {
      DLog(" -> EpicCommand::execute() -> not found: %s\n", e.c_str());
    }

    return Command::execute();
  }
} // Wallet Namespace
