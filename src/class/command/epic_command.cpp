
#include "debug.hpp"
#include "epic_command.hpp"
#include "class/epic.hpp"
#include "class/mutable_wallet.hpp"

namespace Wallet
{
  int EpicCommand::execute()
  {
    DLog(" -> EpicCommand::execute()\n");

    if (this->options.handle.empty()) {
      throw std::string{"--handle option is needed."};
    }

    MutableWallet wallet{this->options.walletPath};
    wallet.logLevel = this->options.verbose;

    if (this->options.isRemove) {
      DLog(" -> EpicCommand::execute() -> remove\n");
      wallet.removeEpic(this->options.handle);
    } else {
      if (!this->options.title.empty() || !this->options.bgColor.empty()) {
        // Create Epic from Options.
        Epic epic{this->options};

        if (wallet.epicExists(this->options.handle)) {
          DLog(" -> EpicCommand::execute() -> update\n");

          // Update Epic
          wallet.updateEpic(epic);
        } else {
          DLog(" -> EpicCommand::execute() -> create\n");

          // Create Epic
          wallet.addEpic(epic);
        }
      } else
        DLog(" -> EpicCommand::execute() -> do nothing\n");
    }

    return Command::execute();
  }
} // Wallet Namespace
