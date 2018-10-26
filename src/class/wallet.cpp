
#ifdef DEBUG
#include <cstdio>
#endif

#include "wallet.hpp"
#include "entry.hpp"

namespace Wallet
{
  Wallet::Wallet() : path(WALLET_DEFAULT_PATH)
  {
#ifdef DEBUG
    printf("Wallet::Wallet(def '%s')\n", this->path.c_str());
#endif
  }

  Wallet::Wallet(const std::string path) : path(path)
  {
#ifdef DEBUG
    printf("Wallet::Wallet(str '%s')\n", this->path.c_str());
#endif
  }

  Wallet::Wallet(const std::optional<std::string> path) : path(path.has_value() ? *path : WALLET_DEFAULT_PATH)
  {
#ifdef DEBUG
    printf("Wallet::Wallet(opt '%s')\n", this->path.c_str());
#endif
  }

  bool Wallet::add(const Entry entry) noexcept
  {
#ifdef DEBUG
    printf("Wallet::add(%p)\n", &entry);
#endif
    return this->add(entry, false);
  }

  bool Wallet::add(const Entry entry, const bool isUnique) noexcept
  {
#ifdef DEBUG
    printf("Wallet::add(%p, u=%c)\n", &entry, isUnique ? 'Y' : 'N');
#endif

    return false;
  }
}
