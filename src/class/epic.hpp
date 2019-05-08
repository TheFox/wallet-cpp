
#ifndef WALLETCPP_EPIC_HPP_
#define WALLETCPP_EPIC_HPP_

#include <string>

#include "accountable.hpp"

namespace Wallet
{
  class Epic final : public Accountable
  {
  public:
    // Constructor
    Epic() noexcept;

    // Parameter
    std::string id{};
    std::string handle{};
    std::string name{};
    std::string color{};

    // Conversion
    template<typename T>
    T as() const noexcept;
  };
} // Wallet Namespace

#endif // WALLETCPP_EPIC_HPP_
