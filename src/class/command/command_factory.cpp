
#include "command_factory.hpp"
#include "debug.hpp"
#include "command.hpp"
#include "help_command.hpp"
#include "add_command.hpp"
#include "init_command.hpp"
#include "list_command.hpp"
#include "html_command.hpp"
#include "fake_version_command.hpp"

namespace Wallet
{
  void CommandFactory::setup() noexcept
  {
    if (isSetup) {
      // Run setup only one.
      return;
    }
    isSetup = true;

    DLog(" -> CommandFactory::setup()\n");

    // Clear creators.
    creators.clear();

    creators["add"] = []()->std::unique_ptr<Command> {
      return std::make_unique<AddCommand>();
    };
    creators["init"] = []()->std::unique_ptr<Command> {
      return std::make_unique<InitCommand>();
    };
    creators["list"] = []()->std::unique_ptr<Command> {
      return std::make_unique<ListCommand>();
    };
    creators["html"] = []()->std::unique_ptr<Command> {
      return std::make_unique<HtmlCommand>();
    };
    creators["version"] = []()->std::unique_ptr<Command> {
      return std::make_unique<FakeVersionCommand>();
    };
  }

  std::unique_ptr<Command> CommandFactory::makeCommand(const std::string& _name) const
  {
    auto fn = creators[_name];
    if (fn == nullptr) {
      throw (std::string{"Command not found: "} + _name);
    }
    return fn();
  }

  // Private
  bool CommandFactory::isSetup = false;
  std::unordered_map<std::string, std::function<std::unique_ptr<Command>()>> CommandFactory::creators;
} // Wallet Namespace
