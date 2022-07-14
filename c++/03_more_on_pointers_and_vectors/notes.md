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

for (int i = 0; i < 6; ++i)
    for (int j = 0; j < 5; ++j)
        ma[i][j] = 10 * i + j;

for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 5; ++j)
        std::cout << std::setw(3) << ma[i][j];
    std::cout << std::endl;
}

for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 5; ++j)
        std::cout << &ma[i][j] << " ";
    std::cout << std::endl;
}
```

