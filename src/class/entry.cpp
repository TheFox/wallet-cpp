
#ifdef DEBUG
#include <cstdio>
#include <iostream>
#endif

#include <sstream>

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
    printf("Entry::Entry(%p)\n", this);
#endif
  }

  Entry::~Entry()
  {
#ifdef DEBUG
    printf("Entry::~Entry(%p)\n", this);
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

  void Entry::setDate(std::string _date) noexcept
  {
    // TODO: parse date string for date object
    this->date = std::move(_date);
  }

  std::string Entry::getDate() const noexcept
  {
    return this->date;
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
    if (this->date.empty()) {
      out << "undefined";
    } else {
      out << this->date.substr(0, 4); // year
      out << '_';
      out << this->date.substr(5, 2); // month
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
    node["date"] = this->date;
    return node;
  }
} // Wallet Namespace
