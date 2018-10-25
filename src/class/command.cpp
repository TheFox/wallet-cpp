
#include <stdio.h>

#include "command.hpp"

namespace Wallet
{
  Command::Command() : commandOptions({})
  {
    printf("Command::Command(%p)\n", this);
  }

  Command::~Command()
  {
    printf("Command::~Command(%p)\n", this);
  }

  void Command::setOptions(const CommandOptions _commandOptions) noexcept
  {
    this->commandOptions = commandOptions;
  }

  int Command::execute()
  {
    return 0;
  }
} // Wallet Namespace
