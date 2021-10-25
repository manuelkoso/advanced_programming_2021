#include <chrono>
#include <iostream>

//valgrind to detect memory leaks
//another method: fsantize library (g++)

//constexpr: function evalueted at compile and run time (can be evalueted at compile time)
//return types: literals or custom types whose constructor is...
//constexpr has limitation, for example we cannot use std::cout
constexpr std::size_t fib(const unsigned int x) {
  return (x < 2) ? x : fib(x - 1) + fib(x - 2);
  // if (x < 2) return x;
  // else {
  //   return fib(x-1) + fib(x-2);
  // }
}

//constexpr int  i = 0; //the value of i must be known at compile time 

std::size_t fib_rt(const std::size_t x) { //evalueted in runtime
  if (x < 2)
    return x;
  return fib(x - 1) + fib(x - 2);
}

//Meta programming
template <unsigned i> //only integer types, no doubles, no chars...
constexpr std::size_t fib_t() {
  return fib_t<i - 1>() + fib_t<i - 2>();
}

//we cannot do fib_t<n>() => no runtime!!
//this is the differnce with "nomrmal" function

template <>   //base case, specialized a template function for a given value of the template
constexpr std::size_t fib_t<0>() {
  return 0;
}

template <>   //base case
constexpr std::size_t fib_t<1>() {
  return 1;
}

//macros #: add or remove blocks of code at prepocessor
#if __cplusplus > 201700L
//if is eveliated at runtime
//=> with constexpr is evalueted at compiletime
//=> we can add the prevous base cases into the first function fib_t()
template <unsigned i>
constexpr std::size_t fib_t17() {
  if constexpr (i < 2)
    return i;
  else {  // very important
    return fib_t17<i - 1>() + fib_t17<i - 2>();
  }
}
#endif

constexpr unsigned int num{24};

int main() {
  { //define a scope
    auto t0 = std::chrono::high_resolution_clock::now();
    //without constexpr the function can be evaluted at runtime
    constexpr auto x = fib(num);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "constexpr: " << x << " [" << elapsed.count() << " us]"
              << std::endl;
  }

  //here I cannot access to t0...

  {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto x = fib_rt(num);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "run time: " << x << " [" << elapsed.count() << " us]"
              << std::endl;
  }

  {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto x = fib_t<num>();
    auto t1 = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "template: " << x << " [" << elapsed.count() << " us]"
              << std::endl;
  }

#if __cplusplus > 201700L
  {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto x = fib_t17<num>();
    auto t1 = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "c++17: " << x << " [" << elapsed.count() << " us]"
              << std::endl;
  }

#endif

  return 0;
}
