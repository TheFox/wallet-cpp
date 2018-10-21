
#include <any>
#include <map>
#include "command_factory.hpp"
#include "command.hpp"
#include "help_command.hpp"
#include "add_command.hpp"

namespace Wallet
{
  CommandFactory::CommandFactory(const std::string& name) : name(name) {}

  int CommandFactory::execute()
  {
    std::map<std::string, Command*> creators{};
    creators["help"] = new HelpCommand();
    creators["add"] = new AddCommand();

    auto command_ptr = creators[this->name];
    if (command_ptr == nullptr) {
      command_ptr = creators["help"];
    }
    return command_ptr->execute();
  }
} // Wallet Namespace
