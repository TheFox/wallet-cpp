
#ifndef WALLETCPP_ENTRY_HPP_
#define WALLETCPP_ENTRY_HPP_

#include <string>

namespace Wallet
{
  class Entry final
  {
  public:
    // Constructor
    Entry();
    // Destructor
    ~Entry();

    // ID
    void setId(std::string) noexcept;
    std::string getId() const noexcept;

    // Date
    void setDate(std::string) noexcept;
    std::string getDate() const noexcept;

    // Functions
    std::string getFileName() const noexcept;

  private:
    std::string id{};
    std::string date{};
  };
} // Wallet Namespace

#endif // WALLETCPP_ENTRY_HPP_
