
#ifndef WALLETCPP_LOGABLE_HPP_
#define WALLETCPP_LOGABLE_HPP_

#include <string>

namespace Wallet
{
  class Logable
  {
  public:
    // Variables
    mutable std::uint8_t logLevel{0};

  protected:
    // Functions
    void log(const std::string&) const noexcept;
  };
} // Wallet Namespace

#endif // WALLETCPP_LOGABLE_HPP_
