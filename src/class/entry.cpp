
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
    printf("Entry::Entry\n");
#endif

    // TODO
    this->id = "uuid";
  }

  Entry::~Entry()
  {
#ifdef DEBUG
    printf("Entry::~Entry\n");
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
    if (this->date.empty())
      out << "undefined";
    else
      out << this->date.substr(4+1+2);
    out << ".yml";
    return out.str();
  }
} // Wallet Namespace
