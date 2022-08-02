//
// Created by koso on 02/08/22.
//
#define CATCH_CONFIG_MAIN
#include "../include/catch.h"
#include "../include/date.h"



TEST_CASE( "Date initialization with valid date" ) {
    Date date {2, static_cast<month_enum>(5), 2022};
    REQUIRE(date.day() == 2);
    REQUIRE(date.month() == static_cast<month_enum>(5));
    REQUIRE(date.year() == 2022);
}

TEST_CASE( "Date initialization with invalid date (wrong day)" ) {
    Date date {2, static_cast<month_enum>(5), 2022};
    REQUIRE(date.day() == 34);
    REQUIRE(date.month() == static_cast<month_enum>(5));
    REQUIRE(date.year() == 2022);
}

TEST_CASE( "Date initialization with invalid date (wrong month)" ) {
    Date date {2, static_cast<month_enum>(14), 2022};
    REQUIRE(date.day() == 2);
    REQUIRE(date.month() == static_cast<month_enum>(5));
    REQUIRE(date.year() == 2022);
}

TEST_CASE( "Date initialization with invalid date (wrong year)" ) {
    Date date {2, static_cast<month_enum>(5), 2022};
    REQUIRE(date.day() == 2);
    REQUIRE(date.month() == static_cast<month_enum>(5));
    REQUIRE(date.year() == -2022);
}

