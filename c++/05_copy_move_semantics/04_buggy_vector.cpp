#include <iostream>

//why buggy vector? Where is the bug?
//the bug is where I didn't write
template <typename T>
class Vector {
  T* elem;
  std::size_t _size;

 public:
  explicit Vector(const std::size_t length)   //see the explainantion of explicity below
      : elem{new T[length]{}}, _size{length} {}

  ~Vector() { delete[] elem; }

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return elem; }
  T* begin() { return elem; }

  const T* end() const { return elem + size(); }
  T* end() { return elem + size(); }
};

void foo(const Vector<int>& v) {
  std::cout << v.size() << std::endl;
}


int main() {
  Vector<int> v1{3};
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;

  foo(v1);
  //foo(1); //why it compiles if we don't use explicit??
            //because the constructor defines implicity a default foo()
            //to protect ourself from this bug we have to use explict
            //explicity calling a Vector
            //with 1 we are calling the constructor implicity

  std::cout << "v1: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;

  Vector<int> v2{v1};  // synthetized copy constructor
                       // is a good choice?
                       //=> no because the changes of a vector also change the other vector

  //copy by value each element => point the same memory location (SHALLOW COPY)
  //we don't want to copy the value of pointers
  //we want to copy elements (DEEP COPY)

  std::cout << "v2 after default copy ctor: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v1[0] = 99;

  std::cout << "v2 after v1 has been changed: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v2[1] = -999;

  std::cout << "v1 after v2 has been changed: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;

  return 0;

  //there is an error
  //the descrutcor delete the memory of v2
  //the descrutcor want to delete memory of v1
  //but that memory location was already deleted

}
