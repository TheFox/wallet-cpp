
#include "debug.hpp"
#include "epic.hpp"

namespace Wallet
{
  Epic::Epic() noexcept
  {
    DLog(" -> Epic::Epic(%p)\n", this);
  }

  Epic::Epic(const YAML::Node& node) noexcept
  {
    DLog(" -> Epic::Epic(YAML::Node)\n", this);

    if (node["id"].IsDefined()) {
      this->id = node["id"].as<decltype(this->id)>();
    }
    if (node["handle"].IsDefined()) {
      this->handle = node["handle"].as<decltype(this->handle)>();
    }
    if (node["name"].IsDefined()) {
      this->name = node["name"].as<decltype(this->name)>();
    }
    if (node["color"].IsDefined()) {
      this->color = node["color"].as<decltype(this->color)>();
    }
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
