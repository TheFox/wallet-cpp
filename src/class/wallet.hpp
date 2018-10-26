
#ifndef WALLET_WALLET_HPP_
#define WALLET_WALLET_HPP_

namespace Wallet
{
  class Entry;

  class Wallet final
  {
    void add(Entry) noexcept;
  };
} // Wallet Namespace

#endif // WALLET_WALLET_HPP_
