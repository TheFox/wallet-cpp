
#ifndef WALLETCPP_COMPONENTS_HPP_
#define WALLETCPP_COMPONENTS_HPP_

#include <string>

#define DATETIME_FORMAT "%Y-%m-%dT%T"

namespace Wallet
{
  class Components
  {
  public:
    static std::string getNowStr();
  };
}

#endif // WALLETCPP_COMPONENTS_HPP_
