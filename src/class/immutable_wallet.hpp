
#ifndef WALLETCPP_IMMUTABLE_WALLET_HPP_
#define WALLETCPP_IMMUTABLE_WALLET_HPP_

#include "mutable_wallet.hpp"

namespace Wallet
{
  /**
   * Immutable Wallet will not touch the data directory.
   */
   // TODO: remove ImmutableWallet and rename MutableWallet
  class [[deprecated("Use const MutableWallet instead")]] ImmutableWallet : public MutableWallet
  {
  public:
    // Constructor
    explicit ImmutableWallet(std::string);

    // Functions
    void setup() override;
    bool add(const Entry&, bool) override;
  };
} // Wallet Namespace

#endif // WALLETCPP_IMMUTABLE_WALLET_HPP_
