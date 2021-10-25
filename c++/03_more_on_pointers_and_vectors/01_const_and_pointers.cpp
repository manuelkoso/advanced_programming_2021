#include <iostream>

template <typename T>
void print_sentinel(const T* a, const std::size_t l);

int main() {
  int a{8}, b{7};
  int* pi{&a};

  const int* pc{&a};   //protect value through the pointer => *pc
                      //pointer to an integer constant, however I can chenge the value of pointer
  // *pc = 7; 	// error
  a = 15;  // I can obviously change a

  int* const cp{&a};   //const pointer to int (we are protecting the pointer)
  a = b;
  *cp = 33;
  // cp = &b;   // error

  //const pointer != pointer to a const

  const int* const cpc{&a};   //constant pointer to a integer constant

  // *cpc = 0;  // error
  // cpc = &n;  // error
  a = 99;

  //a static array is very close to a const pointer
  //int a[5];

  int aa[4]{};
  print_sentinel(aa, 4);

  return 0;
}

template <typename T>
void print_sentinel(const T* a, const std::size_t l) {
  const T* const end{a + l};  //l jumps of size long long
  for (; a != end; ++a)
    std::cout << *a << std::endl;
}
