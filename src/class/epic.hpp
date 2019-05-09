
#ifndef WALLETCPP_EPIC_HPP_
#define WALLETCPP_EPIC_HPP_

#include <string>

#ifdef __has_include
#  if __has_include(<yaml-cpp/yaml.h>)
#    include <yaml-cpp/yaml.h>
#  else
#    error "Missing <yaml-cpp/yaml.h>"
#  endif
#endif // __has_include

#include "trait/accountable.hpp"

namespace Wallet
{
  class Epic final : public Trait::Accountable
  {
  public:
    // Constructor
    Epic() noexcept;

    // Copy Constructor
    explicit Epic(const YAML::Node&) noexcept;
    explicit Epic(const Epic&) noexcept;

    // Move Constructor
    Epic(Epic&& epic) noexcept;

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
