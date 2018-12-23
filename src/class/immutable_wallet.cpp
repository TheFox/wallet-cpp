
#ifdef DEBUG
#include <cstdio>
#endif

#include "debug.hpp"
#include "immutable_wallet.hpp"
#include "entry.hpp"

namespace Wallet
{
  ImmutableWallet::ImmutableWallet(const std::string path) : MutableWallet(path)
  {
    DLog(" -> ImmutableWallet::ImmutableWallet(opt '%s')\n", this->path.c_str());
  }

  bool ImmutableWallet::add(const Entry entry, const bool isUnique)
  {
    throw std::string{"Read-only Wallet cannot modify data."};
  }

  void ImmutableWallet::setup()
  {
    DLog(" -> ImmutableWallet::setup()\n");

    this->setupVariables();
  }
} // Wallet Namespace
