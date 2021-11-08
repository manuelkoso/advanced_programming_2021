#include <iostream>
#include <memory>

//why buggy vector? Where is the bug?
//the bug is where I didn't write

//smart pointers are found in header memory and are really like unique_ptr
//the simple pointers are called raw pointers

//interface of unique_ptr
//T* .get() => return a raw pointer
//reset(T*) => takes another pointer. If the pointer was pointing to a memory
            //it first release that memory and then it sets its ownership to this new address
//T* release() => return a raw pointer to the memory that it was owning, but release the ownership

template <typename T>
class Vector {
  std::unique_ptr<T[]> elem;  //is constructed by passing an address
  std::size_t _size;

 public:
  explicit Vector(const std::size_t length)
      : elem{new T[length]{}}, _size{length} {}

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return elem.get(); } //using elem.get(), because is a unique pointer
  T* begin() { return elem.get(); }

  const T* end() const { return elem.get() + _size; }
  T* end() { return elem.get() + _size; }
};

int main() {
  Vector<double> v1{7};
  // Vector<double> v2{v1}; // default copy ctor calls a deleted function
  //=> error
  //ERROR: default copy constructor calls a deleted function
  //=> we didn't write delete
  //but unique pointer implemented this concept of the unique ownership by deleting copy constructor
  //and also copy assignment
  //=> compiler: how can I copy two objects? I don't know
  //tipically is not good if we have raw pointers and smart pointers
  //because the compiler is not able to implement a deep copy by itself  
  return 0;
}
