# 02_functions_and_arrays

## The keyword auto
When we use the keyword auto the compiler automatically deduced the type of a variable according by the initialization value. We have to use = with auto not {}.

```c++
auto b = true;          // a bool
auto ch = 'x';          // a char
auto i = 123;           // an int
auto d = 1.2;           // a double
auto z = std::sqrt(d);  // z has the type of whatever sqrt(d) returns
auto ui = 0u;           // unsigned int
auto llui = 0llu;       // long long unsigned int
auto& j = i;            // int&
auto pb = &b;           // pointer to a boolean
```
How can we double check the type deduced by the compiler? We can use the compiler by inforcing a compile error.    

The auto can be also used as return type of a function. When the return type is auto we cannot declare the function, because the compiler will not know the type (compile error).

```c++
auto factorial(unsigned int n);
```

We have to define it.

```c++
auto factorial(unsigned int n) {
  unsigned int ret{1};
  while (n > 1) {
    ret *= n;
    --n;
    // ret *= n--;
  }
  return ret;
}
```
In this case the return type is a unsigned int. 

Auto allows to write a more maintanable code. If we change the type of the local variable ret in the factorial function the first line will throws an error. 

```c++
unsigned int a {factorial(6)};  // whatch out
auto b = factorial(5);
```

## Function overloading
In c++ we can have multiple function with the same name but with different types and numbers of arguments (unlike c). This is a function overloading. Note that overloadnig doesn't work if we have the same types and number of parameters with a different return type, it will be an error. 

```c++
int dwim(const int a, const int b);
double dwim(const double a, const double b);
float dwim(const float a, const float b);
```
If we don't have the float version of the function and we put float numbers as arguments in the dwim, which function will be used, the int or the double version? The double one, because it will be a best matching: the float number is nearer to a double value rather than an int. 

Note (std::cout): 
Printing on the screen is very very slow. std::cout has an internal buffer, doesn't print immediately. If we want to flush the buffer we have to use std::endl.
```c++
std::cout << "Hello" << "/n" 
          << "World" << std::endl;
``` 

## Templates
Template is a placholder which will fed by the compiler. Is up to the compiler to copy and paste the function, substitute it to the template the right types. 

Declaring a function with template
```c++
template <typename T>
T dwim(const T a, const T b);
```

Definning a function with template
```c++
template <typename T>
T dwim(const T a, const T b) {
    return a + b;
}
```

T can be whatever. T used in the signature of the function. The template T lived till the declaration or definition. If we want to use in the main function will be a compile error (in this case).

An example of main that use dwim with templates
```c++
int main() {
  int a{5}, b{7};
  double c{3.332}, d{7.7};
  float e{23.4}, f{3.34e2};
  char g{'0'}, h{'6'};

  std::cout << dwim(a, b) << '\n'
            << dwim(c, d) << '\n' 
            << dwim(e, f) << '\n'
            << dwim(g, h) << std::endl;
  return 0;
}            
```

The compiler figure in out the type of the template. With the template we avoid to write the same function multiple time for different arguments types. 

We can check the type of the template by compiling and then check the .o file. (use the shell command "nm --demangle file.o" to convert the function signature into a more readable one). 

We can also (like auto), check the template type by inforcing a compile error.
```c++
// only declaration to throw an error
template <typename T>
void debug();

void main() {
  auto b = true;
  auto pb = &b;
  debug(pb);
}
```

Another example with template and buil-in types
```c++
template <typename T, int N>
T dwim(const T a, const T b) {
    return a + b + N;
}
```
Here we need to specify the value of N, when we use this function. The value of N must be known at compile time, we cannot put a variable into the <>. The template must be known at compile time. But we can use the const or constexpr for N.

```c++
int a{5}, b{7};
double c{3.332}, d{7.7};
float e{23.4}, f{3.34e2};
char g{'0'}, h{'6'};

constexpr int h {4};

std::cout << dwim<int, 3>(a, b) << '\n'
        << dwim<double, h>(c, d) << '\n' 
        << dwim<float, 3>(e, f) << '\n'
        << dwim<char, 3>(g, h) << std::endl;
```
If we invert the arguments of the template we can ommit the type of the template will be deduced.

```c++
template <int N, typename T>
T dwim(const T a, const T b) {
    return a + b + N;
}
```

```c++
int a{5}, b{7};
double c{3.332}, d{7.7};
float e{23.4}, f{3.34e2};
char g{'0'}, h{'6'};

constexpr int h {4};

std::cout << dwim<3>(a, b) << '\n'
        << dwim<h>(c, d) << '\n' 
        << dwim<3>(e, f) << '\n'
        << dwim<3>(g, h) << std::endl;
```
Templates are performed at compile time, therefore we will not have any runtime penalty. Templates are very efficient.

If we specify the type of the template, this type will be wins over the deduced by the compiler. In the following example the double will be casted into int.
```c++
double c{3.332}, d{7.7};
std::cout << dwim<4>(c, d) << std::endl;
```

## Built-in arrays
An array is a set of cells of the same type. The static arrays live in the stack and cannot change their size. 

```c++
int ai[4];
float af[9];
ai[0] = 9;    // first element
af[8] = 3.3;  // last element
ai[88] = 7;   // undefined behavior, no range checking!!!
double ad[7]{1.1, 2.2, 3.3};  // the rest is set to 0
```
The cells that are not initialized will have a random value.

```c++
for (std::size_t k{0}; k < 4; ++k)
  std::cout << "ai[" << k << "] = " << ai[k] << '\n';

for (std::size_t k{0}; k < 9; ++k)
  std::cout << "af[" << k << "] = " << af[k] << '\n';
```

If we want to have an array initialized with 0s:

```c++
double a[90]{};
```

How is an array stored in memory? In the case of an array of floats, the second cell will be the address of the first cell plus 4bytes.

```c++
// array of float
for (std::size_t k{0}; k < 9; ++k)
  std::cout << "&af[" << k << "] = " << &af[k] << '\n';
```

An array is implicitly converted to a pointer to its first element

```c++
double ad[7]{1.1, 2.2, 3.3}; 
*ad = 9.9; 
```

The array passes by reference by default, beacuase there is a strong relation between array and pointer => a[n] is equal to *(a+n). *(a+n) is an aritmetic pointer operation, with this operation the pointer does n jumps (of the size of the type that it points to).

```c++
void surprise(double a[], const std::size_t n) { //size_t alias for long long unsigned int
  for (auto i = 0llu; i < n; ++i) {
    a[i] = 77;
  }
}
```
```c++
int main() {
  double ad[7]{1.1, 2.2, 3.3}; 
  surprise(ad, 7);
  std::cout << "after surprise()" << std::endl;
  for (std::size_t k{0}; k < 7; ++k)
    std::cout << ad[k] << std::endl;

  return 0;
}
```

The dynamic arrays live in the heap or free store (the other part of the RAM). In order to initialize a dynamic array we have to use the operator new.

```c++
// dynamic array of int
std::size_t n = 4;
int* da{new int[n]};
```
The value n can be known at runtime. The size of a static array must be known at compile time. 

There two important differences between stack and heap:
1. Stack is very small, the heap is the size of our RAM minus the size of the stack
2. Objects created in the stack  are automatically free. Objects that live in heap have to be free by the user, otherwise will be stored "forever".

With the operator delete we release an array.
```c++
delete[] da;
```

Dynamic array is an example of unnamed object. All the object that are in the heap are unnamed object, we don't know the name of this object, we just know the address, which is stored in a proper pointer. 

If we forget to release an array, there will be a memory leak. Valgrind (command shell. valgrind) is a tool to double check if there some memory leaks. 

## How to resize a built-in array

Static array cannot be resized. If we want resize an array at runtime we have to use dynamic arrays. 

```c++
unsigned int size{10};
auto a = new int[size]; // a is a pointer of an array which lives in the heap
```

To resize an array we have to create a new array, copy the values of the prevous array, free the oldest array and set the pinter to point to the new array. 

```c++
const unsigned int new_size {size*2};
auto tmp = new int[new_size];

// copy values
for(unsigned int i = 0; i < size; ++i) {
  tmp[i] = a[i];
}

delete[] a;

a = tmp;
size = new_size;
```

We note that the variables new_size and tmp will live only in this small set of instructions. Therefore is reccomend to use the scope.

```c++
{
  const unsigned int new_size {size*2};
  auto tmp = new int[new_size];

  // copy values
  for(unsigned int i = 0; i < size; ++i) {
    tmp[i] = a[i];
  }

  delete[] a;

  a = tmp;
  size = new_size;
}
```
Once we pass this block the variables new_size and tmp are gone.

Note: after the delete the value of a doesn't change. In RAM is stored a table where the addresses and the sizes of the arrays in the heap. When we use ```new```, we update the table with a new row, when we use ```delete```, the row of the array is removed (now this area can be used for other things). After the delete a is a dangling pointer, it means, that is a pointer, which points to a deleted memory location; ```delete``` doesn't change the bits!

## Constexpr functions

```constexpr``` keyword doesn't guaranteed that function is evaluated at compile time (because a function has the necessity to be evaluated at runtime). The ```constexpr``` function can be evaluated both at compile time and at runtime. Function with ```constexpr``` has one limitation: 
- Arguments and return type must be literal: built-in or custom types whose constructors are ```constexpr``` (for example not std::string)

```c++
constexpr std::size_t fib(const unsigned int x) {
  return (x < 2) ? x : fib(x - 1) + fib(x - 2);
  // if (x < 2) return x;
  // else {
  //   return fib(x-1) + fib(x-2);
  // }
}
```

With template plus constexpr we can do "meta-programming", do things at compile time.
```c++
template <unsigned i> 
constexpr std::size_t fib_t() {
  return fib_t<i - 1>() + fib_t<i - 2>();
}
```
NOTE: Exist two kind of template
- Unkown types - placholder for a type
- Unkown integer types - placeholde for integer numbers (int, short, unsigned, not float or double)

Example of using the above function
```c++
fib_t<5>();
```
When are using recorsion we must define the base cases. In this case we have to specialized a template function. We can do this by using the follwing syntax.
```c++
template <> // base case
constexpr std::size_t fib_t<0>() {
  return 0;
}

template <>   // base case
constexpr std::size_t fib_t<1>() {
  return 1;
}
```
Since C++-17 they introduced the if constexpr. If statement are evaluated at runtime. If constexpr are instead evaluated at compile time.

```c++
template <unsigned i>
constexpr std::size_t fib_t17() {
  if constexpr (i < 2)
    return i;
  else {  // very important
    return fib_t17<i - 1>() + fib_t17<i - 2>();
  }
}
```
If the condition ```i < 2``` is true, the else statement is not compiled. If we use the if statement without constexpr the if and else statemtn will both compiled. 

When we are using constexpr function (without template) we have to use also constexpr variables, otherwise the function can be comupted at runtime.

```c++
constexpr auto x = fib(num);
```

If we increase the input number, the function constexpr (without template) tipically don't do the memoization, don't keep track functions that already been defined. We going to have a compile error. The fibonacci function with template is more robust.

To exclude part of code from the compilation, we use the prepocessor, the macros (```#if```, ```#endif```...).
```c++
#if __cplusplus > 201700L 
template <unsigned i>
constexpr std::size_t fib_t17() {
  if constexpr (i < 2)
    return i;
  else {  // very important
    return fib_t17<i - 1>() + fib_t17<i - 2>();
  }
}
#endif
```
To measure the execution time of a piece of code, we include the ```<crono>``` header and use the namespace crono.

```c++
{
  auto t0 = std::chrono::high_resolution_clock::now();
  auto x = fib_t<num>();
  auto t1 = std::chrono::high_resolution_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
  std::cout << "template: " << x << " [" << elapsed.count() << " us]"
            << std::endl;
}
```