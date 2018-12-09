
#ifndef WALLETCPP_ENTRY_TEST_HPP_
#define WALLETCPP_ENTRY_TEST_HPP_

#ifdef __has_include
#  if __has_include(<catch2/catch.hpp>)
#    define CATCH_CONFIG_MAIN
#    include <catch2/catch.hpp>
#  else
#    error "Missing <catch2/catch.hpp>"
#  endif
#endif // __has_include

#include "../class/entry.hpp"

TEST_CASE("Test Entry", "[entry]"){
  Wallet::Entry entry;

  // Optional
  SECTION("setDate()") {
    entry.setDate("2018-1-2");
    REQUIRE(entry.getDateStr() == "2018-01-02");

    entry.setDate("1492-12-31");
    REQUIRE(entry.getDateStr() == "1492-12-31");
  }

  SECTION("getFileName()") {
    entry.setDate("2018-1-02");
    REQUIRE(entry.getFileName() == "month_2018_01.yml");

    entry.setDate("2018-12-23");
    REQUIRE(entry.getFileName() == "month_2018_12.yml");
  }

  SECTION("Expense"){
    entry.setExpense(1.234);
    REQUIRE(entry.expense == -1.234f);
    REQUIRE(entry.balance == -1.234f);
  }

  SECTION("Revenue"){
    entry.setRevenue(2.345);
    REQUIRE(entry.revenue == 2.345f);
    REQUIRE(entry.balance == 2.345f);
  }

  SECTION("Balance1"){
    REQUIRE(entry.balance == 0.0);

    entry.setRevenue(2.5);
    entry.setExpense(1.23);
    REQUIRE(entry.balance == 1.27f);
  }

  SECTION("Balance2"){
    REQUIRE(entry.balance == 0.0);

    entry.setRevenue(2.5);
    entry.setExpense(3);
    REQUIRE(entry.balance == -0.5f);
  }
}

#endif // WALLETCPP_ENTRY_TEST_HPP_
