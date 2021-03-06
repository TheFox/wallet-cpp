
#include <locale>
#include <sstream> // ostringstream, istringstream
#include <string>
#include <iomanip> // setprecision
#include <ios> // fixed
#include <fstream> // ifstream
#include <ios> // std::ios::beg, std::ios::end

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
  std::string getNowStr(const std::string& format) noexcept
  {
    auto tfacet = std::make_unique<boost::posix_time::time_facet>(format.c_str());
    const std::locale loc(std::cout.getloc(), tfacet.release());

    const auto now = boost::posix_time::second_clock::universal_time();

    std::ostringstream ss{};
    ss.imbue(loc);
    ss << now;

#ifdef DEBUG
    const auto s1 = ss.str();
    return s1;
#else
    return ss.str();
#endif
  }

  std::string ftos(const std::float_t& _f, const int _p) noexcept
  {
    std::ostringstream ss{};
    ss << std::fixed << std::setprecision(_p) << _f;

#ifdef DEBUG
    const auto s1 = ss.str();
    return s1;
#else
    return ss.str();
#endif
  }

  std::float_t stof(std::string _s) noexcept
  {
    std::replace(_s.begin(), _s.end(), ',', '.');
    return std::stof(_s);
  }

  /**
   * @link https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
   */
  Date parseDate(const std::string& _s) noexcept
  {
    using Tokenz = std::vector<std::uint16_t>;

    // String Items
    Tokenz tokens{};
    std::string token{};
    std::istringstream tokenStream{_s};
    while (std::getline(tokenStream, token, '-')) {
      tokens.push_back(static_cast<Tokenz::value_type>(std::stoi(token)));
    }

    Date ymd{0, 0, 0};
    switch (tokens.size()) {
      case 1:
        if (tokens.at(0) < 2001) {
          // Now
          const auto now = boost::posix_time::second_clock::universal_time();

          ymd.year = now.date().year();
          ymd.month = now.date().month();
          ymd.day = tokens.at(0);
          break;
        }
        ymd.year = tokens.at(0);
        break;

      case 2:
        if (tokens.at(0) >= 2001) {
          ymd.year = tokens.at(0);
          ymd.month = tokens.at(1);
        } else {
          // Now
          const auto now = boost::posix_time::second_clock::universal_time();

          ymd.year = now.date().year();
          ymd.month = tokens.at(0);
          ymd.day = tokens.at(1);
        }
        break;

      case 3:
        ymd.year = tokens.at(0);
        ymd.month = tokens.at(1);
        ymd.day = tokens.at(2);
        break;

      default:
        break;
    }
    return ymd;
  }

  std::string readFileIntoString(const std::string& path) noexcept{
    // File Handle
    // https://stackoverflow.com/a/2602258
    std::ifstream fh{path};

    // Get File size.
    fh.seekg(0, std::ios::end);
    const auto fileSize1 = static_cast<std::streamoff>(fh.tellg());
    const auto fileSize2 = static_cast<std::size_t>(fileSize1);
    fh.seekg(0, std::ios::beg);

    // String
    std::string str(fileSize2, ' ');

    // Read file into String.
    fh.read(&str[0], fileSize2);

    // Close template file.
    fh.close();

    return str;
  }
} // Wallet::Components Namespace
