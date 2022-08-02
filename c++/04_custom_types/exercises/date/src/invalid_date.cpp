//
// Created by koso on 02/08/22.
//

#include <string>
#include "../include/date.h"

class Date::InvalidDate {
    std::string _message;

    InvalidDate(std::string message) : _message{message} {};

    const char* what() const {
        return _message.c_str();
    }

};
