#include <iostream>
#include <string>

//the idea is to replicate the std::vector

template <typename T>
class Vector {
  //T& data; => is legit, but don't use reference => use pointer
  T* elem;
  std::size_t _size;

 public:
  Vector(const std::size_t size) : elem{new T[size]}, _size{size} {}

  // automatically release the acquired memory
  ~Vector() { delete[] elem; }

  // try to remove the const and recompile
  std::size_t size() const { return _size; }  //const: I don't modify the state _size

  T& operator[](const std::size_t i) {    //attention => no const
    // ++i;
    return elem[i];
  }


 template <typename T>
 void foo0(const Vector<T>& v){
    //premise: the function size is the following:
    //std::size_t size() { return _size; }
    //v.size();   //does it compile?
    //no because actually modifies tha state of the object
    //we have to put const to the function size
    //=> I cannot modify the state of the object

 }

  //operator [] to access the element of the vector
  // try to comment this line and recompile
  const T& operator[](const std::size_t i) const { return elem[i]; }    //we put the second const
                                                                        //for the same prevous reason
  T& operator[](const std::size_t i) const {return element[i];}
  //with this function I can do the following:
  //v[2] = 4;

  //to use for-each we have to define begin and end
  const T* begin() const { return elem; }
  T* begin() { return elem; }

  const T* end() const { return elem + _size; }
  T* end() { return elem + _size; }
};

template <typename T>
void foo(const Vector<T>& x) {
  auto p = x.begin();
  ++p;
}
//if we will define this function in the class
//we must add the keyword friend
//and we can ommit the template, because we are inside the class
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (auto i = 0u; i < v.size(); ++i)
    os << "v[" << i << "] = " << v[i] << std::endl;
  /*
    for(const auto& x : v) {    //we have to define begin and end
    os << x << " ";
  }
  os << std::endl;
  */
  return os;
}

int main() {
  Vector<double> v{10};
  std::cout << v[1] << '\n';
  return 0;
  for (auto i = 0u; i < v.size(); ++i)
    v[i] = i;

  std::cout << v << std::endl;

  Vector<double>* pv{&v};

  // first dereference the pointer, then I can use the defined operators
  (*pv)[0] = -99.999;

  pv->operator[](1) = 77777.3333;  // or I call the function by name

  std::cout << *pv << std::endl;

  Vector<double>& rv{v};

  rv[5] = 555;

  std::cout << v << std::endl;

  return 0;
}
