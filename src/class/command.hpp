
#ifndef WALLETCPP_COMMAND_HPP_
#define WALLETCPP_COMMAND_HPP_

#include "command_options.hpp"

namespace Wallet
{
  class Command
  {
  public:
    Command() noexcept;
    virtual ~Command() = 0;
    virtual int execute() = 0;
    void setOptions(CommandOptions) noexcept;

  protected:
    CommandOptions commandOptions{};
  };
} // Wallet Namespace

#endif // WALLETCPP_COMMAND_HPP_
