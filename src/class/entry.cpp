
#ifdef DEBUG
#include <cstdio>
#endif

#include <sstream>
#include "entry.hpp"

namespace Wallet
{
  Entry::Entry()
  {
#ifdef DEBUG
    printf("Entry::Entry(%p)\n", this);
#endif

    // TODO: set initial rand UUID
    this->id = "uuid";
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
  };

  void Entry::setDate(std::string _date) noexcept
  {
    // TODO: parse date string for date object
    this->date = std::move(_date);
  }

  std::string Entry::getDate() const noexcept
  {
    return this->date;
  };

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
} // Wallet Namespace
