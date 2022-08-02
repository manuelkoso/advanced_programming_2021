cmake_minimum_required(VERSION 3.23)
project(date VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# create file date_config.h containing the version
configure_file(include/date_config.h.in include/date_config.h)

add_subdirectory(src)
add_subdirectory(test)
enable_testing()
add_test(NAME Test_Date COMMAND TestDate)

add_executable(date main.cpp src/date.cpp src/helper_functions.cpp src/invalid_date.cpp)

target_link_libraries(date PUBLIC Date)

# Since the configured file will be written into the binary tree,
# we must add that directory to the list of paths to search for include files.
target_include_directories(date PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src")




