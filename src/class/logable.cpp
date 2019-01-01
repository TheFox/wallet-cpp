
#include <iostream>

#include "logable.hpp"

namespace Wallet
{
  void Logable::log(const std::string& message) const noexcept
  {
    if (this->logLevel == 0) {
      return;
    }

    std::cout << message << std::endl;
  }
} // Wallet Namespace
