
#ifdef DEBUG
#include <cstdio>
#endif

#include "command.hpp"

namespace Wallet
{
  Command::Command() noexcept : commandOptions({})
  {
#ifdef DEBUG
    printf(" -> Command::Command(%p)\n", this);
#endif
  }

  Command::~Command()
  {
#ifdef DEBUG
    printf(" -> Command::~Command(%p)\n", this);
#endif
  }

  void Command::setOptions(const CommandOptions _commandOptions) noexcept
  {
    this->commandOptions = _commandOptions;
  }

  int Command::execute()
  {
    return 0;
  }
} // Wallet Namespace
