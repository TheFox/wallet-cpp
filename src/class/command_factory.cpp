
#include <map>
#include <functional>
#include <memory>
#include "command_factory.hpp"
#include "command.hpp"
#include "help_command.hpp"
#include "add_command.hpp"
#include "init_command.hpp"
#include "html_command.hpp"

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
    //creators["help"] = []()->std::unique_ptr<Command> {
    //  return std::make_unique<HelpCommand>();
    //};
    creators["add"] = []()->std::unique_ptr<Command> {
      return std::make_unique<AddCommand>();
    };
    creators["init"] = []()->std::unique_ptr<Command> {
      return std::make_unique<InitCommand>();
    };
    creators["html"] = []()->std::unique_ptr<Command> {
      return std::make_unique<HtmlCommand>();
    };
  }

  std::unique_ptr<Command> CommandFactory::getCommand(const std::string& _name) const
  {
    auto fn = creators[_name];
    if (fn == nullptr) {
      throw (std::string{"Command "} + _name + " not found.");
    }
    return fn();
  }

  // Private
  bool CommandFactory::isSetup = false;
  std::map<std::string, std::function<std::unique_ptr<Command>()>> CommandFactory::creators;
} // Wallet Namespace
