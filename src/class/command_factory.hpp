
#ifndef WALLET_COMMAND_FACTORY_HPP_
#define WALLET_COMMAND_FACTORY_HPP_

#include <string>

namespace Wallet
{
  class CommandFactory final
  {
  public:
    CommandFactory(const std::string&);
    int execute();
  private:
    const std::string name;
  };
}

#endif // WALLET_COMMAND_FACTORY_HPP_
