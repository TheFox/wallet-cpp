
#ifdef DEBUG
#include <cstdio>
#include <iostream>
#endif

#include <sstream>
#include <string_view>

#ifdef __has_include
#  if __has_include(<yaml-cpp/yaml.h>)
#    include <yaml-cpp/yaml.h>
#  else
#    error "Missing <yaml-cpp/yaml.h>"
#  endif
#  if __has_include(<boost/uuid/uuid.hpp>)
#    include <boost/uuid/uuid.hpp>
#    include <boost/uuid/random_generator.hpp>
#    include <boost/uuid/uuid_io.hpp>
namespace uuid = boost::uuids;
#  else
#    error "Missing <boost/uuid/uuid.hpp>"
#  endif
#endif // __has_include

#include "entry.hpp"

namespace Wallet
{
  Entry::Entry()
  {
#ifdef DEBUG
    printf(" -> Entry::Entry(%p)\n", this);
#endif
    using gregorian::date;
    using gregorian::day_clock;

    this->date = day_clock::local_day();
  }

  Entry::~Entry()
  {
#ifdef DEBUG
    printf(" -> Entry::~Entry(%p)\n", this);
#endif
  }

  void Entry::setId(std::string _id) noexcept
  {
    this->id = std::move(_id);
  }

  std::string Entry::getId() const noexcept
  {
    return this->id;
  }

  void Entry::setTitle(std::string _title) noexcept
  {
    this->title = std::move(_title);
  }

  std::string Entry::getTitle() const noexcept
  {
    return this->title;
  }

  void Entry::setDate(const std::string _dateStr)
  {
    using gregorian::date;
    using gregorian::days;
    using gregorian::day_clock;
    using gregorian::from_simple_string;
    using gregorian::from_undelimited_string;
    using gregorian::from_us_string;
    using gregorian::from_uk_string;
    using gregorian::to_iso_extended_string;
    using std::string_view_literals::operator ""sv;

    // Yesterday
    constexpr std::string_view yesterdayStr = "yesterday"sv;
    bool isYesterday = false;
    if (_dateStr.length() <= yesterdayStr.length()) {
      isYesterday = yesterdayStr.substr(0, _dateStr.length()) == _dateStr;
    }

    // Tomorrow
    constexpr std::string_view tomorrowStr = "tomorrow"sv;
    bool isTomorrow = false;
    if (!isYesterday && _dateStr.length() <= tomorrowStr.length()) {
      isTomorrow = tomorrowStr.substr(0, _dateStr.length()) == _dateStr;
    }

    if (isYesterday) {
      // Today
      date today = day_clock::local_day();

      this->date = today - days(1);
    } else if (isTomorrow) {
      // Today
      date today = day_clock::local_day();

      this->date = today + days(1);
    } else {
      // Parse date string.
      try {
        this->date = from_simple_string(_dateStr);
      }
      catch (std::exception& e) {
        try {
          this->date = from_undelimited_string(_dateStr);
        }
        catch (std::exception& e) {
          try {
            this->date = from_us_string(_dateStr);
          }
          catch (std::exception& e) {
            try {
              this->date = from_uk_string(_dateStr);
            }
            catch (std::exception& e) {
              throw std::string_view{e.what()};
            }
          }
        }
      }
    }

#ifdef DEBUG
    std::cout << " -> date: " << to_iso_extended_string(this->date) << std::endl;
#endif
  }

  std::string Entry::getDateStr() const noexcept
  {
    using gregorian::to_iso_extended_string;
    return to_iso_extended_string(this->date);
    //return std::string{};
  }

  void Entry::generateRandomId() noexcept
  {
    using uuid::random_generator;
    using uuid::uuid;
    using std::stringstream;

    // Random UUID
    random_generator gen;
    uuid _id = gen();

    // Convert UUID to String.
    stringstream uuidStream;
    uuidStream << _id;

    // Set ID from String Stream.
    this->id = uuidStream.str();
  }

  std::string Entry::getFileName() const noexcept
  {
    std::ostringstream out;
    out << "month_";
    if (this->date.is_not_a_date()) {
      out << "undefined";
    } else {
      out << this->getDateStr().substr(0, 4); // year
      out << '_';
      out << this->getDateStr().substr(5, 2); // month
    }
    out << ".yml";
    return out.str();
  }

  /**
   * Convert to YAML::Node.
   */
  template<>
  YAML::Node Entry::as() const noexcept
  {
    YAML::Node node(YAML::NodeType::Map);
    node["id"] = this->id;
    node["title"] = this->title;
    node["date"] = this->getDateStr();
    return node;
  }
} // Wallet Namespace
