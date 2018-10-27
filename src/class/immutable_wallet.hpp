
#ifndef WALLETCPP_IMMUTABLE_WALLET_HPP_
#define WALLETCPP_IMMUTABLE_WALLET_HPP_

#include "mutable_wallet.hpp"

namespace Wallet
{
  class ImmutableWallet : public MutableWallet
  {
  public:
    // Constructor
    explicit ImmutableWallet(std::string);

    // Functions
    void setup() noexcept override;
    bool add(Entry, bool) override;
  };
} // Wallet Namespace

#endif // WALLETCPP_IMMUTABLE_WALLET_HPP_
