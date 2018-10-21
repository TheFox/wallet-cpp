
#include <any>
#include <map>
#include <functional>
#include "command_factory.hpp"
#include "command.hpp"
#include "help_command.hpp"
#include "add_command.hpp"

namespace Wallet
{
  void CommandFactory::setup()
  {
    if (isSetup)
      return;
    isSetup = true;

    printf("CommandFactory::setup()\n");

    // @todo Using raw pointer is bad.
    creators2.clear();
    creators2["help"] = []()->Command*{ return new HelpCommand(); };
    creators2["add"] = []()->Command*{ return new AddCommand(); };
  }

  CommandFactory::CommandFactory() : name("") {}
  CommandFactory::CommandFactory(const std::string& name) : name(name) {}

  std::function<Command*()> CommandFactory::getCommandFn(const std::string& _name)
  {
    return creators2[_name];
  }

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

  // Private
  bool CommandFactory::isSetup = false;
  std::map<std::string, std::function<Command*()>> CommandFactory::creators2;
} // Wallet Namespace
