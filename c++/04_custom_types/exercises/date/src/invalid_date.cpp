//
// Created by koso on 02/08/22.
//

#include <string>
#include "../include/date.h"

Date::InvalidDate::InvalidDate(std::string message): _message{message} {};

const char *Date::InvalidDate::what() const {
    return _message.c_str();
}



