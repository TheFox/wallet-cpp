
#ifndef WALLETCPP_COMMAND_HPP_
#define WALLETCPP_COMMAND_HPP_

#include <string>

namespace Wallet
{
  struct CommandOptions
  {
    std::string walletPath = ".wallet";

    // Status
    bool isInteractively;
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

#endif // WALLETCPP_COMMAND_HPP_
