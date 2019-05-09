
#ifndef WALLETCPP_TRAIT_LOGABLE_HPP_
#define WALLETCPP_TRAIT_LOGABLE_HPP_

#include <string>

namespace Wallet::Trait
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
} // Wallet::Trait Namespace

#endif // WALLETCPP_TRAIT_LOGABLE_HPP_
