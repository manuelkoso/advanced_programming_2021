#include <cmath>
#include <iostream>

int main() {
  //c++ is statically typed language
  //the compiler must know the type of a variable
  //auto: compiler deduced automatically the type
  //when use auto don't use {} => use =
  auto b = true;          // a bool
  auto ch = 'x';          // a char
  auto i = 123;           // an int
  auto d = 1.2;           // a double
  auto z = std::sqrt(d);  // z has the type of whatever sqrt(d) returns
  auto ui = 0u;           // unsigned int
  auto llui = 0llu;       // long long unsigned int

  auto& j = i;  // int&

  for (auto i = 0; i < 7; ++i)
    std::cout << i << std::endl;

  auto pb = &b;  // guess what.. How can I know? => pinter boolean
                //we can use compiler to tell us the type of a variable => inforce a error

  debug(pb);    //TODO

  auto s = "hello";  // watch out!

  return 0;
}
