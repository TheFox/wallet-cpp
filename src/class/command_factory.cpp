
#include <any>
#include <map>
#include <functional>
#include <memory>
#include "command_factory.hpp"
#include "command.hpp"
#include "help_command.hpp"
#include "add_command.hpp"

namespace Wallet
{
  void CommandFactory::setup() noexcept
  {
    if (isSetup) {
      return;
    }
    isSetup = true;

    printf("CommandFactory::setup()\n");

    creators.clear();
    creators["help"] = []()->std::unique_ptr<Command> {
      return std::make_unique<HelpCommand>();
    };
    creators["add"] = []()->std::unique_ptr<Command> {
      return std::make_unique<AddCommand>();
    };
  }

  std::unique_ptr<Command> CommandFactory::getCommand(const std::string& _name) const noexcept
  {
    auto fn = creators[_name];
    auto cmd = fn();
    return cmd;

    //if (_name == "help")
    //  return std::make_unique<HelpCommand>();
    //if (_name == "add")
    //  return std::make_unique<AddCommand>();

    // Default
    //return std::make_unique<HelpCommand>();
  }

  Command* CommandFactory::getCommandPtr(const std::string& _name)
  {
    if (_name == "help")
      return new HelpCommand();
    if (_name == "add")
      return new AddCommand();

    // Default
    return new HelpCommand();
  }

  // Private
  bool CommandFactory::isSetup = false;
  std::map<std::string, std::function<std::unique_ptr<Command>()>> CommandFactory::creators;
} // Wallet Namespace
