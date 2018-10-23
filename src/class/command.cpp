
#include <stdio.h>

#include "command.hpp"

namespace Wallet
{
  Command::Command()
  {
    printf("Command::Command(%p)\n", this);
  }

  int Command::execute()
  {
    return 0;
  }

  Command::~Command()
  {
    printf("Command::~Command(%p)\n", this);
  }
} // Wallet Namespace
