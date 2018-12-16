
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

#include "../debug.hpp"
#include "entry.hpp"
#include "../components.hpp"

namespace Wallet
{
  Entry::Entry() noexcept
  {
    //DLog(" -> Entry::Entry(%p)\n", this);

    using calendar::date;
    using calendar::day_clock;

    this->date = day_clock::local_day();
  }

  Entry::Entry(const CommandOptions& options) noexcept : Entry()
  {
    //DLog(" -> Entry::Entry(%p, CommandOptions %p)\n", this, &options);

    // ID
    if (options.id.empty()) {
      this->generateRandomId();
    } else {
      this->id = options.id;
    }

    // Title
    this->title = options.title;

    // Date
    if (!options.date.empty()) {
      this->setDate(options.date);
    }
    // DLog(" -> set date: %s\n", this->date.to_iso_extended_string().c_str());
    calendar::to_iso_extended_string(this->date);

    // Revenue
    this->revenue = options.revenue;

    // Expense
    this->expense = options.expense;

    // Balance
    this->calcBalance();
    DLog(" -> set balance %.2f\n", this->balance);

    // Category
    this->category = options.category;

    // Comment
    this->comment = options.comment;
  }

  Entry::Entry(const YAML::Node& node) noexcept
  {
    //DLog(" -> Entry::Entry(%p, YAML::Node)\n", this);

    if (node["id"].IsDefined()) {
      this->id = node["id"].as<decltype(this->id)>();
    }
    if (node["title"].IsDefined()) {
      this->title = node["title"].as<decltype(this->title)>();
    }
    if (node["date"].IsDefined()) {
      this->date = calendar::from_string(node["date"].as<std::string>());
    }
    if (node["revenue"].IsDefined()) {
      this->revenue = node["revenue"].as<decltype(this->revenue)>();
    }
    if (node["expense"].IsDefined()) {
      this->expense = node["expense"].as<decltype(this->expense)>();
    }
    if (node["balance"].IsDefined()) {
      this->balance = node["balance"].as<decltype(this->balance)>();
    }
    if (node["category"].IsDefined()) {
      this->category = node["category"].as<decltype(this->category)>();
    }
    if (node["comment"].IsDefined()) {
      this->comment = node["comment"].as<decltype(this->comment)>();
    }
  }

  void Entry::setDate(const std::string _dateStr)
  {
    //DLog(" -> Entry::setDate(%s)\n", _dateStr.c_str());

    using std::string_view;
    using calendar::date;
    using calendar::days;
    using calendar::day_clock;
    using std::string_view_literals::operator ""sv;

    // Yesterday
    constexpr string_view yesterdayStr = "yesterday"sv;
    bool isYesterday = false;
    if (_dateStr.length() <= yesterdayStr.length()) {
      isYesterday = yesterdayStr.substr(0, _dateStr.length()) == _dateStr;
    }

    // Now
    constexpr string_view nowStr = "now"sv;
    bool isNow = false;
    if (_dateStr.length() <= nowStr.length()) {
      isNow = nowStr.substr(0, _dateStr.length()) == _dateStr;
    }

    // Tomorrow
    constexpr string_view tomorrowStr = "tomorrow"sv;
    bool isTomorrow = false;
    if (!isYesterday && _dateStr.length() <= tomorrowStr.length()) {
      isTomorrow = tomorrowStr.substr(0, _dateStr.length()) == _dateStr;
    }

    if (isYesterday) {
      // Today
      const date today = day_clock::local_day();

      this->date = today - days(1);
    } else if (isNow) {
      // Today
      const date today = day_clock::local_day();

      this->date = today;
    } else if (isTomorrow) {
      // Today
      const date today = day_clock::local_day();

      this->date = today + days(1);
    } else {
      // Parse date string.
      try {
        this->date = calendar::from_simple_string(_dateStr);
      }
      catch (std::exception& e) {
        try {
          this->date = calendar::from_undelimited_string(_dateStr);
        }
        catch (std::exception& e) {
          try {
            this->date = calendar::from_us_string(_dateStr);
          }
          catch (std::exception& e) {
            try {
              this->date = calendar::from_uk_string(_dateStr);
            }
            catch (std::exception& e) {
              throw std::string{e.what()};
            }
          }
        }
      }
    }

    DLog(" -> date: %s\n", calendar::to_iso_extended_string(this->date).c_str());
  }

  std::string Entry::getDateStr() const noexcept
  {
    return calendar::to_iso_extended_string(this->date);
  }

  std::string Entry::getCategoryHtml() const noexcept
  {
    if (this->category == "default")
      return std::string{" "};

    return this->category;
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
    // Create node.
    YAML::Node node(YAML::NodeType::Map);

    // Set parameters.
    node["id"] = this->id;
    node["title"] = this->title;
    node["date"] = this->getDateStr();
    node["revenue"] = Components::ftos(this->revenue);
    node["expense"] = Components::ftos(this->expense);
    node["balance"] = Components::ftos(this->balance);
    node["category"] = this->category;
    node["comment"] = this->comment;

    return node;
  }
} // Wallet Namespace
