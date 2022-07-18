# 05_copy_move_semantics

## Compiler generated constructors

We have a few different type of constructors. Consider the following code

```c++
#include <iostream>

struct X {
  char member;
  char member2{'d'};
};

int main() {
  X x1;                 // default ctor
  X x2{x1};             // copy ctor 
  X x3{std::move(x2)};  // move ctor
  X x4{};               // default ctor calling {} to each member
  x4 = x3;              // copy assignment
  X x5;                 // default ctor
  x5 = std::move(x4);   // move assignment
  std::cout << x5.member << std::endl;  // what do you expect?? => random value, because is the x1.member, which is uninitialized (add to {} x1 to see what happen)
  return 0;
}
```
If we use `X x1` the built-in type are left uninitialized, while in the case of `X x4{}` the built-in are initialized to default values (e.g 0 for integer). Therefore there is adifference between the two statements.  

A move is similar to a swap. x5 "steals" whatevere was stored in x4. 

If we don't write anything inside the struct, the compiler synthesizes/creates a lot of functions, in specific:

- default constructor
- move constructor
- copy constructor
- copy assignment 
- move assignment
- destructor.

```c++
struct foo {
  foo(); // default ctor
  foo(const foo& x); // copy ctor
  foo(foo&& x); // move ctor

  foo& operator=(const foo& x); // copy assignment
  foo& operator=(foo&& x); // move assignment

}
```

If there are no custom ctors I can directly initialize the members. Note that I need access (i.e. they must be public). It is called aggregate initialization.
```c++
struct S {
  int a;
  double b;
  std::string s;  
};
S s2{1, 2.3, "alberto"};  
```

## Default and delete keyword

When we declare a default value for the members of a class we do the in-class initialization.

```c++
struct X {
  int a = 5;  // in-class initialization
  double b;
  char c = 'a';
  X() = default;  // in-class initializers are used by the constructors
};
```

With `X() = default;` we explicitly ask to the compiler to generate default functions (move, copy, default constructor and so on).

```c++
X x1;    // compiler-generated default ctor
X x2{};  // compiler-generated default ctor calls {} on uninitialized vars
```

If we consider the following struct

```c++
struct Y {
  int a = 77;
  double b;
  char c = 'a';
  Y() : a{5} {}  // what it is written here wins the in-class initialization
  Y(const Y&) = delete;    
};
```

With `delete` we ask to the compiler to delete one or more default function. In this ask we are going to delete a copy constructor. 

```c++
Y y3{y2}; // error: call a deleted function
```
Why are we want to use the default keyword if the compiler creates that function automatically? => the compiler doesn't  always creates these functions (for example when we define a custom cinstructor, the compiler will not create them and in other cases like this). 

NOTE (for the buggy vector): the copy constructor created by the compiler will copy by value => will point to the same array. Use the default constructors/functions if there is no pointer in members. 

The `std::unique_ptr<T[]>` is a smart pointer, that release automatically the memory.  