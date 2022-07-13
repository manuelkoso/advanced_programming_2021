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
How can we double check the type deduced by the compiler? We can use the compiler by inforcing an error.    

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

We can check the type of the template by compiling and then check the .o file. (use the shell command "nm --demangle file.o" to convert the function signature into a more readable one)

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
An array is a set of cells of the same type. 

```c++
int ai[4];
float af[9];
ai[0] = 9;    // first element
af[8] = 3.3;  // last element
ai[88] = 7;   // undefined behavior, no range checking!!!
```

