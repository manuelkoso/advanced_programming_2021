# 06_error_handling

Typically in C if there is an error we returned -1, but this technique is fragile, because  there are some functions which by design they have to return a number.   

```c++
#include <cmath>
#include <iostream>

int main() {
  double d = std::sqrt(4);
  std::cout << d << " " << errno << std::endl;

  d = std::sqrt(-4);
  std::cout << d << " " << errno << std::endl;

  return 0;
}
```

In C there is a macro called errno that if something wet wrong inside a function you change the errno number with a different value. 

If we handled an error we need to remember to set errno to 0. 


## Exception

An example of exceptions (like java).

```c++
#include <cmath>
#include <iostream>

// implment a square root function that "deals with" negative
// numbers. Moreover according to the logic of the program, d should
// never be greater than 50
double square_root(const double d);

struct Negative_number {};

struct Bigger_than_expected {};

int main() {
  try {
    std::cout << "please insert a number\n";
    double number;
    std::cin >> number;
    auto d = square_root(number);
    std::cout << "square root of " << number << " is " << d << '\n';
    return 0;
  } catch (const Negative_number) {
    std::cerr << "The square root of a negative number is a complex number.\n"
                 "square_root() is "
              << "limited to handle positive double numbers.\n";
    return 1;
  } catch (const Bigger_than_expected) {
    std::cerr << "The function square_root has been called with a parameter "
                 "greater than 50.\n"
              << "This means there is a bug in the algorithm that generated "
                 "this number.\n";
    return 2;
  } catch (...) {   // to check all the exceptions 
    std::cerr << "Unknown exception. Aborting.\n";
    return 3;
  }
}

double square_root(const double d) {
  // test the pre-conditions
  if (d < 0)
    throw Negative_number{};
  if (d > 50)
    throw Bigger_than_expected{};
  return std::sqrt(d);
}
```

It's better to define a message into the exceptions structs.

```c++
#include <cmath>
#include <iostream>
#include <string>
#include <utility>

// implment a square root function that "deals with" negative
// numbers. Moreover according to the logic of the program, d should
// never be greater than 50
double square_root(const double d);

struct Square_root_invalid {
  std::string message;
  Square_root_invalid(std::string s) : message{std::move(s)} {}
};

int main() {
  try {
    std::cout << "please insert a number\n";
    double number;
    std::cin >> number;
    auto d = square_root(number);
    std::cout << "square root of " << number << " is " << d << '\n';
    return 0;
  } catch (const Square_root_invalid& s) {
    std::cerr << s.message << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n";
    return 3;
  }
}

double square_root(const double d) {
  // test the pre-conditions
  if (d < 0)
    throw Square_root_invalid{"Cannot handle negative numbers. You gave me " +
                              std::to_string(d)};
  if (d > 50)
    throw Square_root_invalid{
        "The argument of square_root must be lower than 50. You gave me " +
        std::to_string(d)};
  return sqrt(d);
}
```

## Assert

The assertions (and checks) are performed only when the code is compiled without the -DNDEBUG flag.  Assertions are never enough. Put as many assertions as you can without any worry for loss of performance (in release).

The error instead are always checked. 

## Stack unwinding

When we allocate a portion of memory with raw pointes (dynamic array) we have to be sure that this portion of memory hes to be release => use try with catch

```c++
class ManyResources {
  double* ptr;
  Vector v;

 public:
  ManyResources() : ptr{nullptr}, v{3} {
    std::cout << "Manyresources" << std::endl;
    try {
      ptr = new double[5];  // new(std::nothrow) double[5] could be better
      AP_ERROR(false) << "Error in ManyResources ctor." << std::endl;
    } catch (...) {
      delete[] ptr;  // <----
      throw;         // re-throw
    }
  }

  ~ManyResources() {
    std::cout << "~Manyresources" << std::endl;
    delete[] ptr;  // <----
  }
};

```

The reccomendetion is to use smart pointers like unique pointers. 

If we are sure that a function doesn't throw an exeption we can put the keyword `noexcept`. If this keyword is present the compiler will create a faster code. 

```c++
class Vector {
  std::unique_ptr<double[]> elem;

 public:
  Vector(const unsigned int l) : elem{new double[l]} {}

  Vector(Vector&&) noexcept = default;
  Vector& operator=(Vector&&) noexcept = default;

  double& operator[](const unsigned int i) noexcept { return elem[i]; }

  const double& operator[](const unsigned int i) const noexcept {
    return elem[i];
  }

  ~Vector() noexcept { std::cout << "~Vector\n"; }
};
```

What we should mark with `noexcept`? For sure the move semantics because we are stealing resources, the [] operator (we are not aquiring new resources), destructors (without std::cout, std::cout can throw an exception...) and so on.

If we throw an exception within a function `noexcept` the program exit immediately (don't do it).

Study the [RAII](https://en.cppreference.com/w/cpp/language/raii) design pattern. (for the exam)  