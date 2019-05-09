
#ifndef WALLETCPP_TRAIT_IDABLE_HPP_
#define WALLETCPP_TRAIT_IDABLE_HPP_

#include <string>

namespace Wallet::Trait
{
  class Idable
  {
  public:
    // Variables
    std::string id{};

  protected:
    // Functions
    void generateRandomId() noexcept;
  };
} // Wallet::Trait Namespace

#endif // WALLETCPP_TRAIT_IDABLE_HPP_
