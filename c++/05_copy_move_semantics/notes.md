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


## Buggy vector

The copy constructor created by the compiler will copy by value => will point to the same array. Use the default constructors/functions if there is no pointer in members. 

The `std::unique_ptr<T[]>` is a smart pointer, that releases automatically the memory.  

The file 04_buggy_vector contains a buggy implementation of a vector, because doesn't copy properly the vectors. We are just copying the address => we will change the the element of the first vector by changing the second, because all of of both vectors have the address. 

The file 05_buggy_vector contains a buggy implementation of a vector, because I cannot copy the vector, the unique pointer express the idea of the unique ownership by deleting the copy constructor and copy assignment. 

In the 06_copy_move we finally find a good basic implementation of vector, we define the copy semantics (in particular the deep copy, not shallow like in the file 04). The unique pointer doesn't support the copy semantics, but they support the move semantics (because remains unique, we don't have a copy).

If we have raw pointers the default copy and move semantics will not work (depend of the behavior of the class). The move is a simple copy for built-in types (raw pointer for example).   

How the compiler understand which operator, between move and copy, to use? Reference with one & are called l-value reference, reference with two && are called r-value reference. The difference between of two is that the r-value has no name and cannot be on the left side in an assignment. The l-value cannot be on the right. We enforce the r-value by using `std::move`

```c++
Vector<double> v3{std::move(v1)}; 
```

When we return an object by value (not by reference), the compiler implicity does a move assignment since C++-11 (before was a copy assignment). This is called NRVO (Named Return Value Optimization)

```c++
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
  const auto size = lhs.size();

  Vector<T> res(size);
  for (std::size_t i = 0; i < size; ++i)
    res[i] = lhs[i] + rhs[i];

  return res;   
}
```

## The keyword explicit

If we consider the following struct

```c++
struct foo{
  int a;
  foo(const int a): a{a} {}   // implicit conversion from int to foo
}
```

A constructor that can be invoked with just one argument defines an implicit conversion between the argument of the constructor to the type of the class itself. Therefero if we do as follows

```c++
void bar(const foo& f) {
  std::cout << f.a << std:endl;
}

int main() {
  int a{5};
  foo f{5};

  bar(a);  // implicit conversion takes place

}
```

The compiler doesn't complain and the program will print 5 on the standard output, because of the implicit conversion (the constructor is invoked and a new object foo will be created). 

If we want to avoid this behaviour we have to use the keyword explicit.

```c++
struct foo{
  int a;
  explicit foo(const int a): a{a} {}   
}
```

Now this conversion will happen only when we are constructing an object. 

It makes sense to use explicit only if we have constructor with one argument. Pay attention: if the constructor have one argument with the default argument and another without there will be the implicit conversion (see the code below).

```c++
struct foo{
  int a;
  explicit foo(const int a, const double d = 9): a{a} {}   
}
```