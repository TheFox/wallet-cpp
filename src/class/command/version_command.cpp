
#include <iostream>

#include "config.hpp"
#include "version_command.hpp"

namespace Wallet
{
  int VersionCommand::execute()
  {
    std::cout << PROJECT_NAME << ' ' << PROJECT_VERSION_FULL << " (" << PROJECT_VERSION_HASH << ')' << std::endl;
    std::cout << PROJECT_COPYRIGHT << std::endl;
    std::cout << PROJECT_HOMEPAGE_URL << std::endl;

    return Command::execute();
  }
} // Wallet Namespace
