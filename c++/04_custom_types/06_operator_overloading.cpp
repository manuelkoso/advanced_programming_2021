#include <array>
#include <iostream>
#include <vector>

//std::cout << x;
//=> operator<<(std::cout,x)
//operator in c++ is a function and can be invoked in cleaner way

struct Point_s {
  double x;
  double y;
};  // note ; at the end

//operator overloading
std::ostream& operator<<(std::ostream& os, const Point_s& p) {  //ostream = output steam
  os << "Struct. x = " << p.x << "; y = " << p.y << std::endl;
  return os;
}

class Point_c {
  double x;
  double y;
  //function friend => access to the your private data
  //if we remove friend, we have a compile error
  //complaining about three parameters => two arguments + this
  //friend makes actually 2 things:
  //1 - external function access to private data
  //2 - make this function not a member function
  friend std::ostream& operator<<(std::ostream& os, const Point_c& p) {
    os << "Class. x = " << p.x << "; y = " << p.y << std::endl;
    return os;
  }

};  // note ; at the end

//size of the custom types:
//at least the sum of the size of the members
//sizeof(class) >= sum of: sizeof(member var)
//function doesn't occupy spaces

//IMPORTANT NOTE
//how should I pass a custom type? (value or reference or const reference)
//a pointer in our architecture is 8bytes
//when a struct/class is bigger than a pointer (we are talking about sizes)
//it should be better to pass it by reefrence
//instead of a char (1byte) is convinient to pass it by value

int main() {
  Point_s ps;
  ps.x = 9.9;
  ps.y = 3. / 7;

  std::cout << ps;

  Point_c pc;
  // pc.x =7.6; // error
  std::cout << pc;

  Point_s* p = &ps;
  p->x = 0.0;
  std::cout << *p;  // operator overloading does not work with pointers
  std::cout << p << '\n';
  return 0;
}
