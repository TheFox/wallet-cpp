
#include <locale>

//#include <boost/locale/date_time.hpp>

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

namespace Wallet
{
  std::string Components::getNowStr()
  {
    auto tfacet = std::make_unique<boost::posix_time::time_facet>(DATETIME_FORMAT);
    const std::locale loc(std::cout.getloc(), tfacet.release());

    const auto now = boost::posix_time::second_clock::universal_time();

    std::stringstream nowStream;
    nowStream.imbue(loc);
    nowStream << now;

#ifdef DEBUG
    const auto s1 = nowStream.str();
    return s1;
#else
    return nowStream.str();
#endif
  }
}
