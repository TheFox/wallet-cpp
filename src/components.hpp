
#ifndef WALLETCPP_COMPONENTS_HPP_
#define WALLETCPP_COMPONENTS_HPP_

#include <string>
#include <cmath>

#define DATETIME_FORMAT "%Y-%m-%dT%T%Q"
//#define DATE_FORMAT "%Y-%m-%d"

namespace Wallet::Components
{
  std::string getNowStr();
  std::string ftos(const std::float_t&, int = 2);
  std::float_t stof(std::string);
}

#endif // WALLETCPP_COMPONENTS_HPP_
