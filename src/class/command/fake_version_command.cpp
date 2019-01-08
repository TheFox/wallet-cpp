
#include <iostream>

#include "config.hpp"
#include "fake_version_command.hpp"

namespace Wallet
{
  int FakeVersionCommand::execute()
  {
    std::cout << "COMMAND DEPRECATED" << std::endl;

    return Command::execute();
  }
} // Wallet Namespace
