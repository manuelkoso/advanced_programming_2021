#include "include/date_config.h"
#include <iostream>

#include "include/date.h"
#include "include/helper_functions.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // report version
        std::cout << "Date" << " version: " << date_VERSION_MAJOR << "."
                  << date_VERSION_MINOR << " " << std::endl;
    }
    Date d {1 , static_cast<month_enum>(2), 2389};
    return 0;
}
