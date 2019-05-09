
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
    DLog(" -> Epic::Epic(YAML::Node)\n");

    if (node["id"].IsDefined()) {
      this->id = node["id"].as<decltype(this->id)>();
    }
    if (node["handle"].IsDefined()) {
      this->handle = node["handle"].as<decltype(this->handle)>();
    }
    if (node["name"].IsDefined()) {
      this->name = node["name"].as<decltype(this->name)>();
    }
    if (node["bg_color"].IsDefined()) {
      this->bgColor = node["bg_color"].as<decltype(this->bgColor)>();
    }
  }

  // Copy Contructor
  Epic::Epic(const Epic& epic) noexcept
  {
    DLog(" -> Epic::Epic(%p, %p) [COPY]\n", this, &epic);

    this->id = epic.id;
    this->handle = epic.handle;
    this->name = epic.name;
    this->bgColor = epic.bgColor;
  }

  // Move Constructor
  Epic::Epic(Epic&& epic) noexcept
  {
    DLog(" -> Epic::Epic(%p, %p) [MOVE]\n", this, &epic);

    this->id = std::move(epic.id);
    this->handle = std::move(epic.handle);
    this->name = std::move(epic.name);
    this->bgColor = std::move(epic.bgColor);
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
    node["bg_color"]  = this->bgColor;

    return node;
  }
} // Wallet Namespace
