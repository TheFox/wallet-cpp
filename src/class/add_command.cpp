
#include <stdio.h>

#include "add_command.hpp"
#include "wallet.hpp"

namespace Wallet
{
  int AddCommand::execute()
  {
#ifdef DEBUG
    printf("Add '%d' '%s'\n", this->commandOptions.walletPath.has_value(), (*this->commandOptions.walletPath).c_str());
#endif

    Wallet wallet;

    return Command::execute();
  }
}
