
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

    // Title
    void setTitle(std::string) noexcept;
    std::string getTitle() const noexcept;

    // Date
    void setDate(std::string) noexcept;
    std::string getDate() const noexcept;

    // Functions
    void generateRandomId() noexcept;
    std::string getFileName() const noexcept;

    // Conversion
    template<typename T>
    T as() const noexcept;

  private:
    // Variables
    std::string id{};
    std::string title{};
    std::string date{};

    // Functions
  };
} // Wallet Namespace

#endif // WALLETCPP_ENTRY_HPP_
