# 01_intro

## The simplest program

The simplest program in c++ is the empty main function. Every c++ program must have/need exact one main function. This program does exact one thing: return a value. The value can be checked by the following shell command: echo $? (in the case of the empty main the value will be 0)

## Hello world and compilation steps

We can use the command shell c++ (clang compiler) to compile the c++ source code. By using this command we will create a file named a.out. But if we use the flag -o we can select the name of the output file. 

The goal of the compilation is to transform our source code to a binary file that can be executed by the computer. The compilation has two phases:
- From file .cpp to .o (real compilation: c++ -c src.cpp)
- From file .o to .out (linked phase ld: c++ src.o)

During the linked phase we collect all the .o files plus all the external things. 

The real compilation phase has more phases:
- from .cpp to .cpp' (prepocessor: c++ -E src.cpp)
- from .cpp' to .s (we obtain the assembly file: c++ -S src.cpp)
- from .s to .o (c++ -c src.cpp)

The prepocessor convert the #include <iostream> in the content of the file <iostream>. The #include means copy and paste the content of the <iostream>. 

If we don't have a main function in the source the linker will comply. 

C++ is a strongly typed language:
Each simbol (variable or a function) has a unique type and that type cannot be changed. 

C++ is a staticaly typed language:
Compiler maust know the types of each symbols at the compile time

=> so what is the type of std::cout? Is writtern in the file iostream. That is why we have to include the iostream.

## Type, object, value and variable

- Type: is a implementation of a concept. We distinguish built-in types (int, boolean, char...) and custom types (string...). 
- Object: portion of memory that has an address corresponding to the first cell. We know when the object is finished because of the type of the object (we know the size of the occupied memory).  
- Value: sequence of bits that is contained in the memory occupied by the object. The value is interpreted according to the type. 
- Variable: named object

## Built-in types

Since C++-11 has been introduced universal and uniform initializer {}, is the default way to initialize variables.

Here we creating an object in memory RAM whose value (the sequence of bits) will be interpreted according to the type int
```c++
int a{-1};
```
Some examples of integer types: int, long long, long, unisgned int. For floating numbers we have double, float... . Char is for symbols. Bool is for boolean values (true is 1 and false is 0).
```c++
bool x = true;
char a = 'c';
long double var = 2.32434324323423443243L; // use L otherwise it will be casted to normal double
```

In c++ numbers have a fixed amount of memory. The size of an integer can change according to the type of the machine (laptop, phone, supercomputer and so on) If we want to check the size in bytes of an int, we have to use the sizeof function.
```c++
// check the size of a variable type
std::cout << "on my machine the size of an int is " << sizeof(int) << " bytes\n";
```
If you want to make sure an int is e.g. 2 bytes 
```c++
int16_t small_int{};
std::cout << "on every machine the size of variable small_int is "
        << sizeof(small_int) << " bytes\n";
```

If we want to use the string type (is a custom type, is not buil-in) we have to include the string file. 
```c++
#include <string>
... 
std::string s{"Hello, World!\n"};
...
```

Narrowing effect
```c++
int a = 6.9; // convert to 6
int a {6.9}; // compile error/warning
int a {int(6.9)} // suppress the error/warning with a cast
```
Possible operations:
```c++
// Augmented operations
var += 7;
var -= 7;
var *= 7;
var /= 7;
var %= 7;
var++;  //post incremet
++var;  //pre increment (first increment thevarible and then we use the incremented value)

var = a + b;  // works also for strings
var = a - b;
var = a * b;
var = a % var;  // modulus operator just between integers

// bit-wise operations
int x = var & a;  // AND, 101 & 001 --> 001
x = var | a;      // OR,  101 | 001 --> 101
x = var ^ a;      // XOR, 101 ^ 001 --> 110

x &= a;
x |= a;
x ^= a;

x = 1 << 3;   // 8
x = 16 >> 2;  // 4

x <<= 2;  // 16
x >>= 3;  // 2

bool test;
test = a == b;
test = a < b;
test = a > b;
test = a <= b;
test = a >= b;
test = a != b;
```

The keyword const is a declaration of intent. It means that the value of that variable won't be changed. There are two reason to use the keyword const:
- Compiler can check if the value of that variable chenged
- If the compiler knows that a value won't change can perform a better optimization and consequetly increase performance of our program

```c++
const int a {-4};
```

The keyword constexpr garantees that the computation of an expresion is done in the compile time
```c++
const int a {2};
int b {4};
constexpr double c{a * 8.1234 / 2};
constexpr double d{b * 8.1234 / 2}; // error, b is a variable that is evaluated in runtime
```

Using the library iomanip
```c++ 
#include <iomanip> 
```
```c++
long double lpi = 3.141592653589793238462L;
std::cout << std::setprecision(50) << M_PI << std::endl;
std::cout << std::hex << 43 << std::endl;
std::cout << std::oct << 43 << std::endl;
std::cout << std::dec << 43 << std::endl;
```

## How to read from stdin

The operator cin use the get-from operator ```>>``` (```<<``` is the put-to operator).
```c++
std::cout << "Insert your name and age:\n";
std::string name;
unsigned int age;

std::cin >> name >> age;  //input
std::cout << "Hello, " << name << " [" << age << "]\n";
```
When you have to read a string std::cin stops as soon as he encounters a space. 

## Pointers, references and functions
Reference is initialized with a name with another variable, not with a value. A reference is an alias. A pointer is initialized with an address of a variable. 

```c++
double d {9.9};
double& ref {d};  
// now d and ref are interchangeable
double* ptr {&d}; 
```
The d and ref will have the same value (9.9). The ptr will contain the address of d. The address of d and ref are the same because ref is an alias of d. The address of pointer is different, is placed in another portion of the memory. The addresses are expressed with a hex number. 

The value of variable d can be changed through either ref or ptr as follows
```c++
ref = 7.7;
*ptr = 5.5;
```

Function is a name that you a give to a set of instructions. 

```c++
// Declaring a function (before we use it)
void buggy_swap(int a, int b);  // signature of the function

int main() {
    ...
}
```
```c++
// Defininig a function
void buggy_swap(int a, int b) {
  int tmp = b;
  b = a;
  a = tmp;
}
```
```c++
// Defininig and declaring a function (before we use it)
void buggy_swap(int a, int b) {
  int tmp = b;
  b = a;
  a = tmp;
}

int main() {
    ...
}
```
For the compilation step is enough that the functions are declared. The definitions of the functions (that can be in different external files) are collected and use it in the linked phase. 

When we execute a program, the program and the variables that we created will live in the RAM. The RAM is conceptually divided in two areas:
- heap
- stack

Each function that we run, lived in a different stack frame. The variables of each functions lived in the stack frame of their function. There is no connection between local variables of different functions. When the function execution is over the stack frame of the function is deleted. Therefore the prevous function is called buggy_swap, we worked with the values (passed by value). We have to consider the address of the variables (passed by reference).

```c++
void swap_c(int* a, int* b) {
  int tmp = *b;
  *b = *a;
  *a = tmp;
}

// or (better)
void swap_cxx(int& a, int& b) {
  int tmp = b;
  b = a;
  a = tmp;
}
```

# Watch out

The types a have fixed amount of bytes. We cannot reppresent all the possible numbers, RAM have a limited memory. 

```c++
// the last numbers are negative or 0...
int a = 1;
for (int i = 0; i < 33; ++i) {
    a *= 2;
    std::cout << a << std::endl;
}
```

An int has 4 bytes. The first bit determine the sign of the number: is it is 0 the number is positive, if it is 1 the number is a negative number. When we multiply with 2 we perform a bit left shift. If we are continuing to multiply by 2, the first bit will become 1 => the number becomes negative. If we still multiply by two in the portion of memory will be only 0s (overflow). 

Another common mistake is the comparison between two floating numbers. Never ever use == (or !=) with floating point numbers.
```c++
for (double d = 0.1; d != 1.0; d += 0.1)
    std::cout << d << std::endl;
```

When we have to compare floating numbers we have to do as follows.
```c++
for (double d = 0.1; std::abs(d-1.0) > 1e-15; d += 0.1)
    std::cout << d << std::endl;
```