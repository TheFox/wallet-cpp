
#ifndef WALLETCPP_ENTRY_HPP_
#define WALLETCPP_ENTRY_HPP_

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
} // Wallet Namespace

#endif // WALLETCPP_ENTRY_HPP_
