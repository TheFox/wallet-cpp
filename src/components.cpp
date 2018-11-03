
#include <locale>
#include <sstream>
#include <iomanip>

#ifdef __has_include
#  if __has_include(<boost/date_time/local_time/local_time.hpp>)
#    include <boost/date_time/local_time/local_time.hpp>
#  else
#    error "Missing <boost/date_time/local_time/local_time.hpp>"
#  endif
#  if __has_include(<boost/date_time/time_facet.hpp>)
#    include <boost/date_time/time_facet.hpp>
#  else
#    error "Missing <boost/date_time/time_facet.hpp>"
#  endif
#endif // __has_include

#include "components.hpp"

namespace Wallet::Components
{
  std::string getNowStr()
  {
    auto tfacet = std::make_unique<boost::posix_time::time_facet>(DATETIME_FORMAT);
    const std::locale loc(std::cout.getloc(), tfacet.release());

    const auto now = boost::posix_time::second_clock::universal_time();

    std::stringstream ss;
    ss.imbue(loc);
    ss << now;

#ifdef DEBUG
    const auto s1 = ss.str();
    return s1;
#else
    return ss.str();
#endif
  }

  std::string ftos(const std::float_t _f, const int _p)
  {
    using std::fixed;
    using std::setprecision;

    std::stringstream ss;
    ss << fixed << setprecision(_p) << _f;

#ifdef DEBUG
    const auto s1 = ss.str();
    return s1;
#else
    return ss.str();
#endif
  }
}
