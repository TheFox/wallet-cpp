
#include <sstream> // ostringstream

#ifdef __has_include
#  if __has_include(<boost/uuid/uuid.hpp>)
#    include <boost/uuid/uuid.hpp>
#    include <boost/uuid/random_generator.hpp>
#    include <boost/uuid/uuid_io.hpp>
#  else
#    error "Missing <boost/uuid/uuid.hpp>"
#  endif
#endif // __has_include

#include "debug.hpp"
#include "idable.hpp"

namespace Wallet::Trait
{
  /**
   * Generate a random ID for this Entry.
   */
  void Idable::generateRandomId() noexcept
  {
    //DLog(" -> Idable::generateRandomId()\n");

    // Random UUID
    boost::uuids::random_generator gen{};
    boost::uuids::uuid _id = gen();

    // Convert UUID to String.
    std::ostringstream uuidStream{};
    uuidStream << _id;

    // Set ID from String Stream.
    this->id = uuidStream.str();

    //DLog(" -> Idable::generateRandomId() -> ID '%s'\n", this->id.c_str());
  }
} // Wallet::Trait Namespace
