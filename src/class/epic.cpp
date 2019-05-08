
#ifdef __has_include
#  if __has_include(<yaml-cpp/yaml.h>)
#    include <yaml-cpp/yaml.h>
#  else
#    error "Missing <yaml-cpp/yaml.h>"
#  endif
#endif // __has_include

#include "debug.hpp"
#include "epic.hpp"

namespace Wallet
{
  Epic::Epic() noexcept
  {
    DLog(" -> Epic::Epic(%p)\n", this);
  }

  /**
   * Convert to YAML::Node.
   */
  template<>
  YAML::Node Epic::as() const noexcept
  {
    // Create node.
    YAML::Node node{YAML::NodeType::Map};

    // Set parameters.
    node["id"]     = this->id;
    node["handle"] = this->handle;
    node["name"]   = this->name;
    node["color"]  = this->color;

    return node;
  }
} // Wallet Namespace
