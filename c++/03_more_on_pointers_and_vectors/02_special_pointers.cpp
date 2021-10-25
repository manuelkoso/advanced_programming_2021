#include <cstring>  // strcmp
#include <iostream>

int func1(const char* a);
int func2(const char* a);
void func3(const char* a);

int main() {
  int a{8};
  int* pi{&a};

  char** ppc; //pointer to pointer

  int* ap[7]; //array of pointer

  void* pv{pi};  //can point to whatever
  // *pv; // we cannot dereference void*
  // ++pv; // we cannot increment. Why? => because he doesn't know the type of the object that the pointer pointers
                                          //we have to do a cast
  //cast:
  //in c: (int*)pv
  //we can have different type of cast in c++
  //for void we have ti use static
  int* pi2{static_cast<int*>(pv)};

  //legit because is void
  pv = ppc;
  pv = ap;
  pv = pi;

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

  double* da{new double[5]{}};
  delete[] da;  // dangling pointer: is a pointer that point to a valid memory location
                //                   but that region has been realesed
                //with delete we only say to the operating system that this portion of memory
                //is free and you can use it
  da = nullptr;

  //check if pi is pointing to some
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

  // strings are special type of char[]
  char word[]{"Hello"};
  char word2[]{'H', 'e', 'l', 'l', 'o', 0};
  if (strcmp(word, word2) == 0)  // word == word2 is
                                 // implementation-dependent (it might
                                 // compare the two pointers, i.e. the
                                 // two addresses of word and word2)
    std::cout << "same\n";
  else
    std::cout << "different\n";

  int (*fp)(const char*);
  fp = func1;

  fp("hello");

  fp = &func2;
  fp("world");

  // fp = func3; // error: wrong signature
  auto xx = func3;

  xx("auto");

  decltype(&func3) x = func3;
  x("decltype");

  return 0;
}

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
