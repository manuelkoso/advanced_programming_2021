# 04_custom_types

## Plain enum

Definition of enum.

```c++
enum color { red, yellow, green };
```

Equivalent, where we specify the value.

```c++
enum color{red=0, yellow=1, green=2};
```
```color``` becomes a new type that we can use.

```c++
void dwim(const color c) {
  switch (c) {
    case red:
      std::cout << "option 1: red\n";
      break;
    case yellow:
      std::cout << "option 2: yellow\n";
      break;
    case green:
      std::cout << "option 3: green\n";
      break;
    default:
      std::cout << "unknown option\n";  
      break;
  }
}
```

Use of the function and of the enum in the main (note that we cannot convert int to enum)

```c++
  color opt{red};
  opt = 3; // cannot assign int to enum
  int a{opt};  // but they implicitly convert to integers

  dwim(opt);
  dwim(yellow);

  dwim(2); // error
  dwim(color(2));  // works but why you may want to write this? Don't do it 
  dwim(color(6));  // is not an error => unkown option
```

## Scoped enum

The first difference between plain enum is the presence of the keyword class.

Definition of a scoped enum

```c++
enum class color { red, yellow, green };
```
Equivalent
```c++
enum class color{red=0, yellow=1, green=2};
```

The second difference is in how accessing the value of the enum.

```c++
void dwim(const color c) {
  switch (c) {
    case color::red:
      std::cout << "option 1: red\n";
      break;
    case color::yellow:
      std::cout << "option 2: yellow\n";
      break;
    case color::green:
      std::cout << "option 3: green\n";
      break;
    default:
      std::cout << "unknown option\n";  // should I exit the program?
      break;
  }
}
```
This method of accessing is useful to discriminate different enum with same name values.   

Use of the function and of the enum in the main (note that we cannot convert int to enum)

```c++
color opt{color::red};

dwim(opt);

dwim(color::yellow);

// dwim(2); // error
dwim(color(2));  // works but what why you may want to write this?

dwim(color(6));  // ???
```

Note that the scoped enum don't implicitly convert to integers unlike plain enum (we have to do a static cast).

```c++
opt = 3;     // cannot assign int to enum
// int a = opt; // and they don't implicitly convert to integers
int a{static_cast<int>(opt)};  // cast (use this)
// int a {int(opt)}; //
// int a {(int)opt}; // C-style cast
```

## Namespace

A namespace is something, that enrich the name of a variable with the name of the namespace itself. 

Definition of a namespace

```c++
namespace choose_a_name {

  int variable;
  
  namespace nested {   
    void hello1();
    void hello2();
    void hello3();
  }  // namespace nested

}
```

The fully-qualified-name is the namespace :: the name of the object.

```c++
choose_a_name::variable = 42;
```

```c++
choose_a_name::nested::hello1();
choose_a_name::nested::hello2();
choose_a_name::nested::hello3();
```

How to define the function declared in namespace? We have few options

```c++
void choose_a_name::nested::hello1() {
  std::cout << "hello1 from nested\n"
            << "variable is " << choose_a_name::variable << std::endl;
}
```

By reopen the namespace

```c++
namespace choose_a_name {
  namespace nested {
    void hello2() {
      std::cout << "hello2 from nested\n"
                << "variable is " << variable << std::endl;
    }
  }  
}  
```
With the keyword ```using namespace```

```c++
using namespace choose_a_name;

void nested::hello3() {
  std::cout << "hello3 from nested\n"
            << "variable is " << variable << std::endl;
}
```

## Enum and name clashing (why scoped enum)

If we consider the following example
```c++
#include <iostream>

enum month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

using namespace std;

int main() {
  cout << nov << endl;  
  cout << dec << endl;  // error
  return 0;
}
```
There is an error because exist a function named std::dec (with the statement ` using namespace std; ` all the std symbols are in the global namespace). We have to use scoped enum.

```c++
#include <iostream>

enum class month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

using namespace std;

int main() {
  cout << int(month::nov) << endl;  
  cout << static_cast<int>(month::dec) << endl;  // error
  return 0;
}
```

Note that ` cout << month::nov << endl; ` doesn't compile, because there is no automatic conversion from enum to int.

Another solution is to avoid the ` using namespace std; ` statement.

```c++
#include <iostream>

enum month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

using std::cout;
using std::endl;

int main() {
  cout << nov << endl;  
  cout << dec << endl;  
  return 0;
}
```

## Struct and class

With struct and class (like enum) we can create new type of object. The main difference between them is that the variable, function in struct are as default public, contrary in class they are private as default.

Definition of struct

```c++
struct Point_s {  
    double x;
    double y;
    void print();
};  // note ; at the end

void Point_s::print() {
    std::cout << "Structure. x = " << this->x << "; y = " << y << std::endl;
}
```

Definition of a class

```c++
class Point_c {
    double x;
    double y;
    public:
        void print() {
            std::cout << "Class. x = " << x << "; y = " << y << std::endl;
        }  // note no ; at the end
};   // note ; at the end
```

In case of the struct the function was defined outside the struct, in case of class inside the class. The recommendation is to define into the class/struct whenever the function is short, 2/3 lines of code, otherwise is better to define it outside the class/struct.  

Access the members/functions of a structure/class
```c++
Point_s ps;
ps.x = 9.9;
ps.y = 3. / 7;
ps.print();

Point_c pc;
pc.x =7.6; // error
pc.print(); 
```

Like normal variables we can have pointers and references to our custom types. To access the members through pointers we have to use the narrow operator. If we dereference the pointer we can use the dot operation to access to the members/functions. 

```c++
Point_s* p = &ps;  // pointer
p->x = 0.0;
p->print();
(*p).y = 7; // dereference the pointer

auto& pr = ps;  // reference => alias of ps
++pr.x;
pr.print();
```
Define an array of custom types.

```c++
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
```

## Operator overloading

We can redefine all the operators of our custom types like =, ==, >=, []... 

Instead of define a print function is better (in C++) to overload the operator `<<`. The operator functions have a fixed signature with two arguments.

For the structure

```c++
struct Point_s {
  double x;
  double y;
};  

//operator overloading
std::ostream& operator<<(std::ostream& os, const Point_s& p) {  
  os << "Struct. x = " << p.x << "; y = " << p.y << std::endl;
  return os;
}
```
Now we are overload the operator and we can use it.

```c++
Point_s ps;
ps.x = 9.9;
ps.y = 3. / 7;

std::cout << ps;
```

For the class is better to overload the operator inside the class by using the keyword `friend`. This keyword does two things:
1. An external function can access to private data
2. Make this function not a member function, put this function outside the class

```c++
class Point_c {
  double x;
  double y;

  friend std::ostream& operator<<(std::ostream& os, const Point_c& p) {
    os << "Class. x = " << p.x << "; y = " << p.y << std::endl;
    return os;
  }
};
```

If we remove the `friend` keyword, the compiler will complain the signature of the function, it will tell us that we passed three arguments instead of two (two arguments + this).

Now we are overload the operator and we can use it.

```c++
  Point_c pc;
  std::cout << pc;

  Point_s* p = &ps;
  p->x = 0.0;
  std::cout << *p;  // operator overloading does not work with pointers
  std::cout << p << '\n';
```

The operator overloading doesn't work with the pointers.

## Multiple flags

## Constructors and destructors

The behaviour of the constructors and destructors in class is the same of the struct. The destructor is the function when the object goes out of scope.

We can have constructor overloading, constructor with the same name but deffering on types and number of the arguments. But we can only have one destructor.

```c++
struct Foo {
  int _i;
  double _d;
  std::string _s;

  // custom constructor
  Foo(const int i, const double d,
      const std::string& s); 

  // default constructor
  Foo();  

  // destructor
  ~Foo();  
};
```

Here we define the custom constructor outside the struct. We have two option where to write the construction code: in the body of the constructor or after the last arguments between column and curly braces. 

```c++
Foo::Foo(const int i, const double d, const std::string& s)
    : _i{i},    
      _d{d},   
      _s{s}
// _i, _d, _s must be initialized in the same order they have been declared
// here we can do only initialization, initial value of the member
{ 
  std::cout << "custom ctor\n";
  // if you want/need you can use _i, _d, _s and change their value
  // with the usual notation +,-,=,*, call a function..
  // don't use {} because this notation is reserved for the
  // construction of the variables and at this point they have already
  // been constructed
}
```

If we want only to initialize variables, the reccomendation is to don't do it in the body. The initialization before the body is faster.

Definition of the default constructor outside the struct

```c++
Foo::Foo() {
  std::cout << "default ctor\n";  
}
```
Definition of the destructor outside the struct

```c++
Foo::~Foo() {
  std::cout << "dtor\n";
}
```

It is reccomended to write constructor and destructor inside the class itself. Inside the class we don't need to specify the fully qualified name. 

Use of the constructor in the main

```c++
int main() {
  Foo f0;    // call default ctor
  Foo f1{};  // call default ctor
  // Foo f2(); // compiler error

  Foo f2{8, 2.2, "hello"};
  Foo f2(8, 2.2, "hello");  // don't use   

  // the destructor is called when the variable goes out of scope
  return 0;  
}  
```

Don't use () for constructor, use {}. 

The default value of members when we are using the default constructor depends on the type of the members. If the member is a built-in type, it remains unintialized (random values); if the meber is a custom type, the default constructor (of each member) is invoked.

## Template class

