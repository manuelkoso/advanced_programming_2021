# 08_inheritance

The two most common techniques for reusing functionality are class inheritance and object composition ("is a" and "has a").

Note (no relative to inheritance):

```c++
Snake* p = new Snake{1, 2.3, false};
```

Here we are using the heap.

We can have compile-time (static) polymorphism (with templates)
```c++
template <class T>
void print_animal_template(const T& a) noexcept {
  std::cout << "through template\n";
  a.info();
  a.speak();
}
``` 

Or the run-time (dynamic) polymorphism (pointer or ref to the base class)

```c++
void print_animal(const Animal& a) noexcept {
  std::cout << "through ref\n";
  a.info();
  a.speak();
}
```

To do in a proper way the run-time (dynamic) polymorphism we have use the keywords `virtual` and `ovveride`. 

```c++
struct Animal {
  unsigned int age;
  double weight;

  Animal(const unsigned int a, const double w) : age{a}, weight{w} {
    AP_ERROR(!(weight < 0)) << "invalid weight!\n";
  }

  Animal() : Animal{0, 0} {}  // delegating constructor

  virtual void speak() const = 0;  // pure virtual function ==> abstract class
  virtual void info() const noexcept {
    std::cout << "age:\t" << age << '\n' << "weight:\t" << weight << '\n';
  }

  virtual ~Animal() {}  // why? see file 03_virtual_destructor.cc
};
```

```c++
struct Dog : public Animal {
  void speak() const noexcept override { std::cout << "Bau\n"; }
  Dog() = default;
  Dog(const unsigned int a, const double d) : Animal{a, d} {}
};
```

NOTE: the difference between override and overload:
- overloading: define a new function same name but different arguments 
- overriding: same name and same arguments

A function can be defined pure virtual, we are defining an abstract class. An abstract class cannot instantiate an object.

```c++
virtual void speak() const = 0;  // pure virtual function ==> abstract class
```

When we are using the virtual we increase the size of the class by implicity adding an id of the class and a pointer to a table of virtual functions. Because of this the dynamic binding works. 

Dynamic polymorphism and dynamic binding work just with pointers and references, I cannot passed a derived class by value. 

We can do dynamic cast to check the type of the object
```c++
if (dynamic_cast<const DangerousSnake*>(&a))
    std::cout << "call 911...\n";
```

NOTE: when we have a parent templated class we have to use the keyword `this`
```c++
#include <iostream>

template <typename T>
struct Base {
  void foo() const { std::cout << "base foo" << std::endl; }
};

template <typename T>
struct Derived : public Base<T> {
  void bar() const { this->foo(); }
};

int main() {
  Derived<int> d;
  d.bar();
}
```

Overloading doesn't work through inheritance we have to use the keywork `using`

```c++
#include <iostream>

struct foo {
  void f(int x) { std::cout << "int " << x << std::endl; }
};

struct bar : public foo {
  using foo::f;  // brings all foo::f to this scope
  void f(char x) { std::cout << "char " << x << std::endl; }
};

int main() {
  bar b;
  b.f(33);
}
```