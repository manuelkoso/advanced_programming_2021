#include "my_class.hpp"

//I have to link the cfile my_class and this file together (the files.o)
//Follow these steps:
//g++ -c main_my_class.cpp
//g++ -c my_class.cpp
//g++ main_my_class.o my_class.o -o

int main(int argc, char const *argv[]) {
  point p;
  p.print();
  return 0;
}
