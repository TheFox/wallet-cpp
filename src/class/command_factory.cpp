
#include "command_factory.hpp"
#include "help_command.hpp"
#include "add_command.hpp"

namespace Wallet
{
  CommandFactory::CommandFactory(const std::string& name) : name(name) {}

  int CommandFactory::execute()
  {
    if (name == "help") {
      HelpCommand command = HelpCommand{};
      return command.execute();
    }

    if (name == "add") {
      AddCommand command = AddCommand{};
      return command.execute();
    }

    HelpCommand command = HelpCommand{};
    return command.execute();
  }
} // Wallet Namespace
