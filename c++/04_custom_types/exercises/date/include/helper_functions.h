//
// Created by koso on 02/08/22.
//
#include "date.h"

#ifndef DATE_HELPER_FUNCTIONS_H
#define DATE_HELPER_FUNCTIONS_H

bool isDateValid(const Date date);
bool isDayValid(const int day);
bool isMonthValid(const month_enum month);
bool isYearValid(const int year);

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
std::ostream& operator<<(std::ostream& os, const Date& d);
bool is_leap(const int y);

#endif //DATE_HELPER_FUNCTIONS_H
