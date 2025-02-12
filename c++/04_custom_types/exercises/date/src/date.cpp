//
// Created by koso on 02/08/22.
//

#include "../include/date.h"

Date::Date(unsigned short day, enum month_enum month, unsigned int year): _d{day}, _m{month}, _y{year} {
    if(!isDateValid()) throw InvalidDate("Invalid date");
};

unsigned int Date::day() const {
    return _d;
}

unsigned int Date::year () const {
    return _y;
}

month_enum Date::month() const {
    return _m;
}

void Date::add_days(const unsigned int day_to_add) {
    _d += day_to_add;
}

bool Date::isDateValid() {
    if(isDayValid() && isYearValid() && isMonthValid()) return true;
    return false;
}

bool Date::isDayValid() {
    if(_d < 1 || _d > 31) return false;
    return true;
}

bool Date::isMonthValid() {
    if((int) _m < 1 || (int) _m > 12) return false;
    return true;
}

bool Date::isYearValid() {
    if(_y < 0) return false;
    return true;
}