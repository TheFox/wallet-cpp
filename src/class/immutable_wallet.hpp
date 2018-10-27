
#ifndef WALLETCPP_IMMUTABLE_WALLET_HPP_
#define WALLETCPP_IMMUTABLE_WALLET_HPP_

#include "mutable_wallet.hpp"

namespace Wallet
{
  class ImmutableWallet : public MutableWallet
  {
  public:
    bool add(Entry) override;
    bool add(Entry, bool) override;

  protected:
    // Functions
    void setup() noexcept override;
  };
} // Wallet Namespace

#endif // WALLETCPP_IMMUTABLE_WALLET_HPP_
