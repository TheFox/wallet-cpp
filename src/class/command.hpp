
#ifndef WALLET_COMMAND_HPP_
#define WALLET_COMMAND_HPP_

#include <string>

namespace Wallet
{
  struct CommandOptions
  {
    std::string appPath;
  };

  class Command
  {
  public:
    Command();
    virtual ~Command() = 0;
    virtual int execute() = 0;
    void setOptions(CommandOptions commandOptions) noexcept;

  protected:
    CommandOptions commandOptions;
  };
} // Wallet Namespace

#endif // WALLET_COMMAND_HPP_
