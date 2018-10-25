
//#include <stdio.h>
//#include <iostream>

#ifdef __has_include
#  if __has_include(<fmt/printf.h>)
#    include <fmt/printf.h>
#  else
#     error "Missing <fmt/printf.h>"
#  endif
#endif

#include "help_command.hpp"

namespace Wallet
{
  int HelpCommand::execute()
  {
    using fmt::print;
    print("Usage: {}\n", this->commandOptions.appPath);

    return 3;
  }
} // Wallet Namespace
