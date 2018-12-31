
#include <iostream>

#include "config.hpp"
#include "version_command.hpp"

namespace Wallet
{
  int VersionCommand::execute()
  {
    std::cout << PROJECT_NAME << ' ' << PROJECT_VERSION << std::endl;
    std::cout << PROJECT_COPYRIGHT << std::endl;

    return Command::execute();
  }
} // Wallet Namespace
