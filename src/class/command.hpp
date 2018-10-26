
#ifndef WALLET_COMMAND_HPP_
#define WALLET_COMMAND_HPP_

#include <string>
#include <optional>

namespace Wallet
{
  struct CommandOptions
  {
    std::optional<std::string> walletPath{std::nullopt};
  };

  class Command
  {
  public:
    Command();
    virtual ~Command() = 0;
    virtual int execute() = 0;
    void setOptions(CommandOptions) noexcept;

  protected:
    CommandOptions commandOptions;
  };
} // Wallet Namespace

#endif // WALLET_COMMAND_HPP_
