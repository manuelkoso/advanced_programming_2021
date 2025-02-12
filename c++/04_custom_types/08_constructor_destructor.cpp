#include <iostream>
#include <string>

struct Foo {
  int _i;
  double _d;
  std::string _s;

  Foo(const int i, const double d,
      const std::string& s);  // custom constructor

  Foo();  // default constructor

  ~Foo();  // destructor
};

//implementation of the constructor outside the class
Foo::Foo(const int i, const double d, const std::string& s)
    : _i{i},    //initialization space, calling the constructors of each element
      _d{d},    //this space is not mandatory
      _s{s}
// _i, _d, _s must be initialized in the same order they have been declared
{ //body of the constructor
  //when we enter in the body of the constructor the variable have just been initialized

  //_i = i; //we can't use {}, is a copy assignment, _i has been already constructed
  std::cout << "custom ctor\n";
  // if you want/need you can use _i, _d, _s and change their value
  // with the usual notation +,-,=,*, call a function..
  // don't use {} because this notation is reserved for the
  // construction of the variables and at this point they have already
  // been constructed
}

Foo::Foo() {
  std::cout << "default ctor\n";  // what happens to our member variables?
}

Foo::~Foo() {
  std::cout << "dtor\n";
}

std::ostream& operator<<(std::ostream& os, const Foo& f) {
  os << f._i << " " << f._d << " " << f._s << std::endl;
  return os;
}

int main() {
  Foo f0;    // call default ctor
  Foo f1{};  // call default ctor
  // Foo f2(); // compiler error

  Foo f2{8, 2.2, "hello"};
  std::cout << "f0: " << f0 << "f1: " << f1 << "f2: " << f2 << std::endl;

  // the destructor is called when the variable goes out of scope
  //the first variable that is destroyed by a consturtctor is f2, then f1 and at the end f0
  return 0;
}
