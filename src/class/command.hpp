
#ifndef WALLET_COMMAND_HPP_
#define WALLET_COMMAND_HPP_

namespace Wallet
{
  class Command
  {
  public:
    virtual int execute();
  };
} // Wallet Namespace

#endif // WALLET_COMMAND_HPP_
