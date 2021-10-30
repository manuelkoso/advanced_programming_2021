#include <array>
#include <iostream>
#include <vector>
//difference between class and struct (also class can have function)
//=> default visibility of the members
//struct: all simbols are public by deafult (yuo can use private)
//class: all simbols are private by default (you can use public)

//the set of public members in a class is called interface

struct Point_s {  //defined a new type
  double x;
  double y;
  void print();
};  // note ; at the end

void Point_s::print() {
  //this is a pointer that points to the object that invoked that function
  std::cout << "Structure. x = " << this->x << "; y = " << y << std::endl;
}

class Point_c {
  //state of the object
  double x;
  double y;

 //to the user I give a set of public function
 public:
  void print() {
    std::cout << "Class. x = " << x << "; y = " << y << std::endl;
  }  // note no ; at the end
};   // note ; at the end

int main() {
  Point_s ps;
  ps.x = 9.9;
  ps.y = 3. / 7;

  //NOTE
  //point::print() == point::print(point* this)
  //p.print() == point::print(&p)
  ps.print();

  Point_c pc;
  // pc.x =7.6; // error
  pc.print();  // I can access private data through public functions

  Point_s* p = &ps;
  p->x = 0.0;
  p->print();

  auto& pr = ps;
  ++pr.x;
  pr.print();

  Point_s array_of_structs[8];  // built-in array
  array_of_structs[0].x = 1;
  array_of_structs[0].y = 2;

  std::array<Point_s, 5> as;
  as[3].x = 3;

  std::vector<Point_s> vs;
  vs.push_back(ps);
  vs[0].x = 999;
  ps.x = 11;
  ps.print();
  vs[0].print();

  return 0;
}
