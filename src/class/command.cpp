
#include <stdio.h>

#include "command.hpp"

namespace Wallet
{
  int Command::execute()
  {
    return 0;
  }

  Command::~Command()
  {
    printf("Command::~Command()\n");
  }
} // Wallet Namespace
