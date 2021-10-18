#include <iostream>

//c++ passes by value by default
//what about array? => we pass a pointer
//realtion between pointer and array
//a[n] is equal to *(a+n)
void surprise(double a[], const std::size_t n) { //size_t alias for long long unsigned int
  for (auto i = 0llu; i < n; ++i) {
    a[i] = 77;
  }
}

//array a collection of elements with same type (homogenous)
//static array => is placed in stack and doesn't change its size

//stack is a small part of ram... => don't allocate very big array
//=> aloccate them in heap (must not be static)

//pay attention: the compiler doesn't follow the c++ standard => TODO
int main() {
  int ai[4];
  float af[9];
  ai[0] = 9;    // first element
  af[8] = 3.3;  // last element
  ai[88] = 7;   // undefined behavior, no range checking!!!

  for (std::size_t k{0}; k < 4; ++k)
    std::cout << "ai[" << k << "] = " << ai[k] << '\n';

  std::cout << "\n-------------------------------\n\n";

  for (std::size_t k{0}; k < 9; ++k)
    std::cout << "af[" << k << "] = " << af[k] << '\n';

  std::cout << "\n how is an array in memory?\n\n";

  for (std::size_t k{0}; k < 9; ++k)
    std::cout << "&af[" << k << "] = " << &af[k] << '\n';

  std::cout << "\n-------------------------------\n\n";

  double ad[7]{1.1, 2.2, 3.3};  // the rest is set to 0

  *ad = 9.9;  // an array is implicitly converted to
              // a pointer to its first element;
  for (std::size_t k{0}; k < 7; ++k)
    std::cout << ad[k] << std::endl;

  // double ad2[2] {1,2,3,4}; // error

  surprise(ad, 7);
  std::cout << "after surprise()" << std::endl;
  for (std::size_t k{0}; k < 7; ++k)
    std::cout << ad[k] << std::endl;

  return 0;
}
