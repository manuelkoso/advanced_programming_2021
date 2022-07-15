# 03_more_on_pointers_and_vectors

Pointer is a special variable, because through a pointer you have access to two variables:
1. The pointer itself
2. The variable pointed by the pointer

Since we are dealing with two variables we can specify const for the pointer itself, meaning that it cannot points to another variable, or you can specify const for the value of the pointed variable, meaning that we can change the value of this variable. 

```c++
int a{8}, b{7};
const int* pc{&a}; // a pointer to a constant int variable 
// *pc = 7 //error
a = 15;  // I can obviously change a
pc = &b;
```

```c++
int* const cp{&a};   //const pointer to int 
a = b;
*cp = 33;
// cp = &b;   // error
```

```c++
const int* const cpc{&a}; // constant pointer to a contstant int 
// *cpc = 0;  // error
// cpc = &n;  // error
a = 99;
```

This last pointer is useful when we are using the so called sentinel approach. The sentinel approach is used when we are dealing with containers (array, list, vector...).

Consider a static array

```c++
int aa[4]{};
print_sentinel(aa, 4);
```

Where the function print_sentinel is defined as folllows

```c++
template <typename T>
void print_sentinel(const T* a, const std::size_t l) {
  const T* const end{a + l};  // sentinel (one past the last element)
  for (; a != end; ++a)
    std::cout << *a << std::endl;
}
```

The statement ```*end = 3;``` is a bug because this cell doesn't belong to the array (one past the last elementof the array). ``` ++end; ``` is also a bug, is too far from the array. Therefore we have to define double const for the sentinel. 


## Special pointers

Pointer to a pointer
```c++
char** ppc; // array of strings => char * ppc[]
```
Array of pointers to integers
```c++
int* ap[7];
```
Void star (a pointer to void), can be initialized with the value of all the pointers that we want, but before we can use it we have to do a cast. Why? All the pointers have a size of 64 bits, but pointers are defined with the type of the variable pointed to by them and the star. With the value of the pointer we get the address of the first bit of the pointed object, but then with the type of the variable pointed to by them we know how many bits/bytes we have read and interpret the value according of that type. Therefore with the void pointer we don't know the size of the pointed variable, we have to cast it. 

```c++
int a{8};
int* pi{&a};
void* pv{pi};
// *pv; // we cannot dereference void*
// ++pv; // we cannot increment. (we don't know the type)
```

```c++
// void pointer can point to whatever object
pv = ppc;
pv = ap;
pv = pi;
```

In c++ we have different type of cast:
- static: cast performed at compile time
- dynamic: 
- reinterpret cast

Static cast is templated.
```c++
int* pi2{static_cast<int*>(pv)};
```
The big difference between a reference and a pointer is that a pointer can point to nothing.

```c++
pi = nullptr;
ppc = nullptr;
// ap = nullptr;  // error, why?  => ap is like constant pointer (static array), I cannot change te address
ap[0] = nullptr;
int** bbb;
bbb = ap;
pv = nullptr;
pi2 = 0;  // older codes. gets the nullptr. please don't do it

// pi = NULL; // please don't do it
//in some compilers NULL doesn't work
```
A static array is like a constant pointer, we cannot change the address and set it to nullptr. 

To avoid dangling pointers
```c++
double* da{new double[5]{}};
delete[] da;  
da = nullptr;
```
We cannot dereference the nullptr, is not accessible. 

Check if a pointer is a nullptr
```c++
if (pi != nullptr)
    std::cout << "pi is not nullptr and I can dereference it " << *pi
                << std::endl;

if (pi)  //is the same of the prevous if => convert to true if the pointer is not nullptr
    std::cout << "pi is not nullptr and I can dereference it " << *pi
                << std::endl;

if (pi == nullptr)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

if (!pi)  //equal as prevous
    std::cout << "pi is nullptr and I CANNOT dereference it \n";
```

Strings are a special type of ```char[]```. (Reccomendation: use std::string)

```c++
char word[]{"Hello"};   // 6 elements, we need to know when the string is finished
char word2[]{'H', 'e', 'l', 'l', 'o', 0};   // same as prevous
if (strcmp(word, word2) == 0)  
    std::cout << "same\n";
else
    std::cout << "different\n";
```

The statement ```word == word2``` is implementation-dependent (can compare the two pointers), don't use it.

Function pointer/functor - pointers can also point to a function 

Considering the following functions
```c++
int func1(const char* a) {
  std::cout << "1111: " << a << std::endl;
  return 1;
}

int func2(const char* a) {
  std::cout << "2222: " << a << std::endl;
  return 2;
}

void func3(const char* a) {
  std::cout << "3333: " << a << std::endl;
}
```

```c++
// the parentheses are mandatory
int (*fp)(const char*); // pointer to a function that return int and arguments const char*
fp = func1;     // fp = &func1; is the same
fp("hello");

fp = &func2;
fp("world");

auto xx = &func3;

xx("auto");

// decltype allows to not write the type
decltype(&func3) x = func3;
x("decltype");
```

## Command line arguments

```c++
int main(int argc, char* argv[]) {
    ...
}
```
We have two arguments:
1. ```int argc``` : integer, number of arguments + 1 (argv[0])
2. ```char* argv[]```: an array of string, the value of arguments, argv[0] is the name of the exacutable

If we want an unisgned int as command line argument, we can use the operator ```>>``` with object ```std::istringstream```.

```c++
unsigned int a;
{
    std::istringstream s{argv[1]};
    s >> a; 
}
std::cout << "a is " << a << std::endl;
```

## Matrices

We can define matrices as follows

```c++
int ma[6][5];  // matrix: 6 rows, 5 columns each

// initialization
for (int i = 0; i < 6; ++i)
    for (int j = 0; j < 5; ++j)
        ma[i][j] = 10 * i + j;

// printing
for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 5; ++j)
        std::cout << std::setw(3) << ma[i][j];
    std::cout << std::endl;
}
```
The matrices are stored in memory as follows: the elements of the same row are consecutive. We can consider the matrix in C++ like a one long array (the last cell of the first row continuos to the first cell of the second row).  

```c++
// printing addresses
for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 5; ++j)
        std::cout << &ma[i][j] << " ";
    std::cout << std::endl;
}
```

How can we pass a matrix to a function? (It's trickier than a simple array)
```c++
void print_ma(int m[][5], int dim1);  // ugly and not flexible 

// second dimension must be knwon at compile time
// void print_ma(int m[][], int dim1, int dim2);  //error 

void print_ma(int* p, int row, int col);  // the "best" solution
```
Function print_ma definition

```c++
void print_ma(int* p, int row, int col) {
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j)
      std::cout << std::setw(2) << p[i * col + j] << " ";
    std::cout << std::endl;
  }
}
```
Use of the function print_ma by using reinterpret_cast.

```c++
// int* pma{ma};     // error
// int* pma[5]{ma};  // error
int* p{reinterpret_cast<int*>(ma)};
// int* p{&ma[0][0]};

// print_ma(ma, 6, 5);  // error
print_ma(p, 6, 5);
```

Define dynamic matrixes

```c++
auto d_ma = new int[6 * 5]{};   //6*5 elements
print_ma(d_ma, 6, 5);
delete[] d_ma;
```

## No built-in arrays (std::array and std::vector)

Static array std::array
```c++
#include <array>
```

Initialization of a static array.
```c++
std::array<int, 4> a{1, 2, 3, 4}; //int = type, 4 is the size
```

We can create an array from another array (the type and the number of elements must be the same)
```c++
std::array<int, 4> b{a}; 
```

Unlike built-in array, where we have to do a for loop to copy an array. We can also do as follows

```c++
b = a;
```

Since C++-11 there is a new type of for loop to go over a container. (range-based fir loops)
```c++
for (auto x : a)
    std::cout << x << " ";
  std::cout << std::endl;
```

Or with the classic way (note the a.size())
```c++
for (auto i = 0u; i < a.size(); ++i)
    std::cout << "a[" << i << "] = " << a[i] << std::endl;
```

Accessing a cell of an array
```c++
a[0] = 0;  // without bound checking
b.at(90);  // bound checking at run-time
```
We have two ways to pass the custom static array to a function.

```c++
// two template
template <typename T, std::size_t N>
void print_array_two(const std::array<T, N>& a);

// one template
template <typename T>
void print_array_one(const T& a);
```
There is a const before the argument, because we have to print and we don't want that the array changes. Morover the compiler will better optimize our code and the program will be faster. 

Implementation of the above functions

```c++
template <typename T, std::size_t N>
void print_array_two(const std::array<T, N>& a) {
  for (const auto& x : a)
    std::cout << x << " ";
  std::cout << std::endl;
}

template <typename T>
void print_array_one(const T& a) {
  for (const auto& x : a)
    std::cout << x << " ";
  std::cout << std::endl;
}
```
NOTE: If we don't use a specific function that we define it, the compiler will ignore it, there will be no effect in runtime.

Example of using
```c++
std::array<int, 4> a{1, 2, 3, 4};
print_array_one(a);
print_array_two(a);
```

Dynamic with std::vector

```c++
#include <vector>
```

Initialization of dynamic array with std::vector. (two ways)

```c++
std::vector<int> v0{1, 2, 4};   // 3 elements
std::vector<int> v1(4, 4);      // 4 elements, each element initialized with 4
```
We can easly copy an array
```c++
v1 = v0; // now v1 has three elements
```

Loop over vector. In the example below we want to add elements to the back of the vector.
```c++
for (auto x : {7, 8, 9})    // {7, 8, 9} is a list
    v1.push_back(x);    
```

We can loop with the classic style intead
```c++
for (auto i = 0u; i < v1.size(); ++i)
    std::cout << "v[" << i << "] = " << v1[i] << std::endl;
```

Accessing the vector
```c++
v1[3];  // not bound checking
v1.at(67);  // bound checking
```

Example of print function 

```c++
template <typename T>
void print_vector(const std::vector<T>& v, const std::string& s) {
  std::cout << s << ": ";
  for (const auto& x : v)
    std::cout << x << " ";
  std::cout << std::endl;
}
```