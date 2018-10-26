
#ifndef WALLET_ENTRY_HPP_
#define WALLET_ENTRY_HPP_

#include <string>

namespace Wallet
{
  class Entry final
  {
  public:
    Entry() = default;

    // ID
    void setId(std::string) noexcept;
    std::string getId() const noexcept;

  private:
    std::string id;
  };
}

#endif // WALLET_ENTRY_HPP_
