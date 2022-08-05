//
// Created by koso on 02/08/22.
//
#include "date.h"

#ifndef DATE_HELPER_FUNCTIONS_H
#define DATE_HELPER_FUNCTIONS_H

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
std::ostream& operator<<(std::ostream& os, const Date& d);
bool is_leap(const int y);

#endif //DATE_HELPER_FUNCTIONS_H
