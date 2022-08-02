//
// Created by koso on 02/08/22.
//

#include <iostream>
#include "../include/helper_functions.h"
#include "../include/date.h"
#include <string>

bool isDateValid(const Date date) {
    if(!isDayValid(date.day())) Date::InvalidDate;
}

bool isDayValid(unsigned int day) {
    if(day < 0 || day > 31) return false;
    return true;
}