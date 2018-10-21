
#ifndef WALLET_COMMAND_FACTORY_HPP_
#define WALLET_COMMAND_FACTORY_HPP_

#include <string>
#include <map>
#include <functional>

#include "command.hpp"

namespace Wallet
{
  class CommandFactory final
  {
  public:
    static void setup();
    CommandFactory();
    CommandFactory(const std::string&);
    std::function<Command*()> getCommandFn(const std::string& name);
    // void getCommandFn();
    int execute();
  private:
    const std::string name;
    static bool isSetup;
    static std::map<std::string, std::function<Command*()>> creators2;
  };
}

#endif // WALLET_COMMAND_FACTORY_HPP_
