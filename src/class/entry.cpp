
#include "entry.hpp"

namespace Wallet
{
  void Entry::setId(std::string _id) noexcept
  {
    this->id = std::move(_id);
  }

  std::string Entry::getId() const noexcept
  {
    return this->id;
  };
}
