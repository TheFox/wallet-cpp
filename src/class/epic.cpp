
#include "debug.hpp"
#include "epic.hpp"
#include "command/command_options.hpp"

namespace Wallet
{
  Epic::Epic() noexcept
  {
    DLog(" -> Epic::Epic(%p)\n", this);

    this->generateRandomId();
    DLog(" -> Epic::Epic(%p) -> ID '%s'\n", this, this->id.c_str());
  }

  Epic::Epic(const CommandOptions& options) noexcept // : Epic()
  {
    DLog(" -> Epic::Epic(CommandOptions) -> ID '%s'\n", this->id.c_str());

    // ID
    if (options.id.empty()) {
      DLog(" -> Epic::Epic(CommandOptions) -> generate new ID\n");
      this->generateRandomId();
    } else {
      DLog(" -> Epic::Epic(CommandOptions) -> set ID from options\n");
      this->id = options.id;
    }

    DLog(" -> Epic::Epic(CommandOptions) -> ID '%s'\n", this->id.c_str());

    this->handle  = options.handle;
    this->title   = options.title;
    this->bgColor = options.bgColor;
  }

  Epic::Epic(const YAML::Node& node) noexcept : Epic()
  {
    DLog(" -> Epic::Epic(YAML::Node) -> ID '%s'\n", this->id.c_str());

    if (node["id"].IsDefined()) {
      DLog(" -> Epic::Epic(YAML::Node) -> get ID from node\n");
      this->id = node["id"].as<decltype(this->id)>();
    }
    // else {
    //   DLog(" -> Epic::Epic(YAML::Node) -> generate new ID\n");
    //   this->generateRandomId();
    //   DLog(" -> Epic::Epic(YAML::Node) -> ID '%s'\n", this->id.c_str());
    // }
    if (node["handle"].IsDefined()) {
      this->handle = node["handle"].as<decltype(this->handle)>();
    }
    if (node["title"].IsDefined()) {
      this->title = node["title"].as<decltype(this->title)>();
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
    this->title = epic.title;
    this->bgColor = epic.bgColor;
  }

  // Move Constructor
  Epic::Epic(Epic&& epic) noexcept
  {
    DLog(" -> Epic::Epic(%p, %p) [MOVE]\n", this, &epic);

    this->id = std::move(epic.id);
    this->handle = std::move(epic.handle);
    this->title = std::move(epic.title);
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
    node["title"]   = this->title;
    node["bg_color"]  = this->bgColor;

    return node;
  }
} // Wallet Namespace
