#include <algorithm>  // std::copy
#include <iostream>
#include <memory>
//the solution
//the copy semantic must be implemented by yourself

//better implementation of swap with move
//move has a computation complexity of size_of()
template <typename T>
void swap(T& x , T& y) {
  auto tmp = std::move(y);  //move constructor
  x = std::move(y);     //move assignment
  y = std::move(tmp);   //move assignment
  //prevous swap:
  //auto tmp = y;  //copy constructor
  //x = y;        //copy assignment
  //y = tmp;      //copy assignment
}

//IMPORTANT
//if we have a raw pointer it means that default move does a copy by value
//when we have raw pointer we have to deal with move and copy by hand

//if we have unique pointer the deafult move is fine

template <typename T>
class Vector {
  std::size_t _size;
  std::unique_ptr<T[]> elem;

 public:
  // custom ctor
  explicit Vector(const std::size_t length)
      : _size{length}, elem{new T[length]{}} {
    std::cout << "custom ctor\n";
  }

  // Vector(const std::initializer_list<T> args)
  //     : _size{args.size()}, elem{new T[_size]} {
  //   std::cout << "list ctor\n";
  //   std::copy(args.begin(), args.end(), begin());
  // }

  // default ctor
  Vector() { std::cout << "default ctor\n"; }  // _size uninitialized
  // Vector() : _size{}, elem{} { std::cout << "default ctor\n"; }

  // this could be better
  // Vector() = default;

  ~Vector() = default;

  /////////////////////////
  // copy semantics

  // copy ctor -- deep copy
  Vector(const Vector& v);

  // copy assignment -- deep copy
  Vector& operator=(const Vector& v);
  // end of copy semantics
  /////////////////////////

  /////////////////////////
  // move semantics
  //steal the resouces => swap that resource with mine

  // move ctor
  Vector(Vector&& v) : _size{std::move(v._size)}, elem{std::move(v.elem)} {
    std::cout << "move ctor\n";
  }

  // Vector(Vector&& v) = default; // ok

  // move assignment
  //call a move to each member
  Vector& operator=(Vector&& v) {
    std::cout << "move assignment\n";
    _size = std::move(v._size);
    elem = std::move(v.elem);
    //what is the state of v? => undefined
    //after a move the state of the object is undefined, but must be a valid state
    //valid state: a state which the destructor can be invoke

    //move access to the underlying structure of the vector, namely the elem and _size
    //move is very fast, because swap the underlying structure
    return *this;
  }

  // Vector& operator=(Vector&& v) = default; // ok

  // end move semantics
  /////////////////////////

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for

  const T* begin() const { return &elem[0]; }
  T* begin() { return &elem[0]; }

  const T* end() const { return &elem[_size]; }
  T* end() { return &elem[_size]; }
};

// copy ctor
template <typename T>
Vector<T>::Vector(const Vector& v) : _size{v._size}, elem{new T[_size]} {
  std::cout << "copy ctor\n";
  std::copy(v.begin(), v.end(), begin());
}

// copy assignment
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
  std::cout << "copy assignment (\n";
  elem.reset();              // clear memory
  auto tmp = v;              // then use copy ctor
  (*this) = std::move(tmp);  // finally move assignment

  // or we do everything by hand..
  // and we can do not reset and call new again if the sizes are suitable

  std::cout << ")\n";
  return *this;  // this is needed to support x=y=z;

  // is this approach consistent with self-assignment vx=vx?

  // for many years, copy assignment was written as follows
  // ~Vector();             // clear memory
  // new (this) Vector{v};  // placement-new on my self using copy ctor
  // return *this;
  // can you imagine why it has been changed?
}

template <typename T>
// why we return by value?
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
  const auto size = lhs.size();

  // what should we do if vectors have differnt sizes? => not now (error handling)

  Vector<T> res(size);
  for (std::size_t i = 0; i < size; ++i)
    res[i] = lhs[i] + rhs[i];

  return res;     //I cannot return by reference, the only way is by value
                  //since c++11 many things passed by value become faster thanks to the move

  //void foo(int& a) => l-value
  //void foo(int&& a) => r-value
  //int a = 5;
  //foo(a); => l-value
  //foo(3); => r-value

  //r-value are all those variables that don't have a name and are going to die immediately
  //=> the variable res is going to die immediately
  //=> is in principle r-value 
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (const auto& x : v)
    os << x << " ";
  os << std::endl;
  return os;
}

int main() {
  std::cout << "Vector<int> v0; calls\n";
  Vector<int> v0;
  std::cout << v0.size() << "\n";
  std::cout << "Vector<int> v00{}; calls\n";
  Vector<int> v00{};
  std::cout << v00.size() << "\n";

  std::cout << "\nVector<double> v1{5}; calls\n";
  Vector<double> v1{5};

  std::cout << "\nVector<double> v2 = v1; calls\n";
  Vector<double> v2 = v1;
  std::cout << "\nv2 = Vector<double>{7}; calls\n";
  v2 = Vector<double>{7};
  std::cout << "\nVector<double> v3{std::move(v1)}; calls\n";
  Vector<double> v3{std::move(v1)};  // now v1 should not be used
  std::cout << "\nv3 = v2; calls\n";
  v3 = v2;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nassign some values to v3\n";
  {
    // auto i = v3.size();
    // while (i--)
    //   v3[i] = i;

    int c = 0;
    for (auto& x : v3)
      x = c++;
  }
  // v3=v3;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nVector<double> v4{v3 + v3}; calls\n";
  Vector<double> v4{v3 + v3};

  std::cout << "v4 = " << v4;

  std::cout << "\nNRVO: Named Return Value Optimization\n";

  std::cout << "\nv4 = v3 + v3 + v2 + v3; calls\n";
  v4 = v3 + v3 + v2 + v3;
  std::cout << "v4 = " << v4;

  return 0;
}
