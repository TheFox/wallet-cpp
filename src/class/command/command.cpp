
#ifdef DEBUG
#include <cstdio>
#endif

#include "command.hpp"

namespace Wallet
{
  Command::Command() noexcept : options({})
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

  int Command::execute()
  {
    return 0;
  }
} // Wallet Namespace
