#include <iostream>

//if I don't define a custom constructor the compiler syntetize/generate a default constructor
//if I don't define a copy constructor the compiler syntetize a copy constructor, a copy assignment and a move constructor and move assignment
//=> this code compile

//signature of the default constructor:
//Foo();

//signature of a copy constructor:
//Foo(const Foo&);  => l-value reference

//signature of a move constructor:
//Foo(Foo&&); => is not a reference to a reference, is a r-value reference

//std:move is a static cast from l-value to r-value reference

//assignment operator
//copy assignment: Foo& operator=(const Foo&);
//move assignment: Foo& operator=(Foo&&);


struct X {
  char member;
  char member2{'d'}; //in class initialization (what is the result with member2?)
};

int main() {
  //X x1;                 // default ctor
  X x1{};               //with this statement what is the result? see initialization of x4
  X x2{x1};             // copy ctor
  X x3{std::move(x2)};  // move ctor
  X x4{};               // default ctor calling {} to each member
  x4 = x3;              // copy assignment
  X x5;                 // default ctor
  x5 = std::move(x4);   // move assignment
  std::cout << x5.member << std::endl;  // what do you expect?? => we are calling the synthetize constructor (of the compiler)
  //result: random
  return 0;
}
