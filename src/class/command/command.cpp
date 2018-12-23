
#include "command.hpp"
#include "debug.hpp"

namespace Wallet
{
  Command::Command() noexcept : options({})
  {
    DLog(" -> Command::Command(%p)\n", this);
  }

  Command::~Command()
  {
    DLog(" -> Command::~Command(%p)\n", this);
  }

  int Command::execute()
  {
    return 0;
  }
} // Wallet Namespace
