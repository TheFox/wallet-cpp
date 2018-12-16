
#ifndef WALLETCPP_COMPONENTS_HPP_
#define WALLETCPP_COMPONENTS_HPP_

#include <string>
#include <vector>
#include <cmath> // float_t

#ifdef __has_include
#  if __has_include(<boost/date_time/year_month_day.hpp>)
#    include <boost/date_time/year_month_day.hpp>
namespace bdt = boost::date_time;
#  else
#    error "Missing <boost/date_time/year_month_day.hpp>"
#  endif
#endif // __has_include

#define DATETIME_FORMAT "%Y-%m-%dT%T+00:00"
#define HUMAN_DATETIME_FORMAT "%Y-%m-%d %T +00:00"

namespace Wallet { namespace Components
{
  // Types
  using Date = bdt::year_month_day_base<std::uint16_t, std::uint16_t, std::uint16_t>;

  // Functions
  std::string getNowStr(std::string = std::string{DATETIME_FORMAT}) noexcept;
  std::string ftos(const std::float_t&, int = 2) noexcept;
  std::float_t stof(std::string) noexcept;
  Date parseDate(const std::string&) noexcept;
}} // Wallet::Components Namespace

#endif // WALLETCPP_COMPONENTS_HPP_
