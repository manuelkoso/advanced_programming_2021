#include <iostream>

struct X {
  char member;
  char member2{'d'}; //in class initialization (what is the result with member2?)
};

//the compiler syntetize... TODO
int main() {
  //X x1;                 // default ctor
  X x1{};               //with this statement what is the result? see initialization of x4
  X x2{x1};             // copy ctor
  X x3{std::move(x2)};  // move ctor
  X x4{};               // default ctor calling {} to each member
  x4 = x3;              // copy assignment
  X x5;                 // default ctor
  x5 = std::move(x4);   // move assignment
  std::cout << x5.member << std::endl;  // what do you expect??
  //result: random
  return 0;
}
