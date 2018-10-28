
#ifdef DEBUG
#include <cstdio>
#endif

#include "immutable_wallet.hpp"
#include "entry.hpp"

namespace Wallet
{
  ImmutableWallet::ImmutableWallet(const std::string path) : MutableWallet(path)
  {
#ifdef DEBUG
    printf("ImmutableWallet::ImmutableWallet(opt '%s')\n", this->path.c_str());
#endif
  }

  bool ImmutableWallet::add(const Entry entry, const bool isUnique)
  {
    throw std::string{"Read-only Wallet cannot modify data."};
  }

  void ImmutableWallet::setup()
  {
#ifdef DEBUG
    printf("ImmutableWallet::setup()\n");
#endif
    this->setupVariables();
  }
} // Wallet Namespace
