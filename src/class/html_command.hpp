
#ifndef WALLETCPP_HTML_COMMAND_HPP_
#define WALLETCPP_HTML_COMMAND_HPP_

#include "command.hpp"

namespace Wallet
{
  class HtmlCommand final : public Command
  {
  public:
    int execute() override;
  };
} // Wallet Namespace

#endif // WALLETCPP_HTML_COMMAND_HPP_
