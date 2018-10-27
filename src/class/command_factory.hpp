
#ifndef WALLETCPP_COMMAND_FACTORY_HPP_
#define WALLETCPP_COMMAND_FACTORY_HPP_

#include <string>
#include <map>
#include <functional>

#include "command.hpp"

namespace Wallet
{
  class CommandFactory final
  {
  public:
    static void setup() noexcept;
    std::unique_ptr<Command> getCommand(const std::string&) const;

  private:
    static bool isSetup;
    static std::map<std::string, std::function<std::unique_ptr<Command>()>> creators;
  };
}

#endif // WALLETCPP_COMMAND_FACTORY_HPP_
