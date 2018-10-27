
#ifdef DEBUG
#include <cstdio>
#endif

#include "immutable_wallet.hpp"
#include "entry.hpp"

namespace Wallet
{
  bool ImmutableWallet::add(const Entry entry)
  {
    throw std::string{"Read-only Wallet cannot modify data."};
  }

  bool ImmutableWallet::add(const Entry entry, const bool isUnique)
  {
    throw std::string{"Read-only Wallet cannot modify data."};
  }

  void ImmutableWallet::setup() noexcept
  {
#ifdef DEBUG
    printf("ImmutableWallet::setup()\n");
#endif
    this->setupVariables();
  }
} // Wallet Namespace
