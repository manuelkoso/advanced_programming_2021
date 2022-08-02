//
// Created by koso on 02/08/22.
//

#ifndef DATE_DATE_H
#define DATE_DATE_H

enum class month_enum {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {

    unsigned short _d;
    month_enum _m;
    unsigned int _y;

public:

    class InvalidDate;

    Date(unsigned short day, enum month_enum month, unsigned int year);

    unsigned int day() const;

    unsigned int year () const;
    month_enum month() const;

    void add_days(const unsigned int day_to_add);

};

#endif //DATE_DATE_H
