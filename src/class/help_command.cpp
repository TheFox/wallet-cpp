
#include <stdio.h>

#include "help_command.hpp"

namespace Wallet
{
  int HelpCommand::execute()
  {
    printf("Help\n");
    return 3;
  }
} // Wallet Namespace
