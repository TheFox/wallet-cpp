
//#include <locale>

#include "boost/date_time/local_time/local_time.hpp"
#include "boost/date_time/time_facet.hpp"

#include "components.hpp"

namespace Wallet
{
  std::string Components::getNowStr()
  {
    // Debug
    //auto timeLocal = boost::posix_time::second_clock::local_time();
    //auto timeLocal = boost::local_time::local_date_time();
    //auto timeUTC = boost::posix_time::second_clock::universal_time();
    //std::cout << "Current System Time = " << timeLocal << std::endl;
    //std::cout << "UTC = " << timeUTC << std::endl;
    //std::cout << "Loc = " << std::cout.getloc().name() << std::endl;

    auto tfacet = std::make_unique<boost::posix_time::time_facet>(DATETIME_FORMAT);
    //auto tfacet = std::make_unique<boost::posix_time::>(DATETIME_FORMAT);
    const std::locale loc(std::cout.getloc(), tfacet.release());

    //auto tfacet_p = new boost::posix_time::time_facet{DATETIME_FORMAT};
    //const std::locale loc(std::cout.getloc(), tfacet_p);

    const auto now = boost::posix_time::second_clock::universal_time();

    std::stringstream nowStream;
    nowStream.imbue(loc);
    nowStream << now;
    //nowStream << timeLocal;
    nowStream << "+00:00";
    //delete tfacet_p;
    return nowStream.str();
  }
}
