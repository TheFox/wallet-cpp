
#include <stdio.h>

#include "add_command.hpp"

namespace Wallet
{
  int AddCommand::execute()
  {
    printf("Add\n");
    return 42;
  }
}
