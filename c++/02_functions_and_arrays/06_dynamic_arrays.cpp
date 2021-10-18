#include <iostream>

//dynamic array: when array is too big or when we don't know the size of the array
int main() {
  std::cout << "Please insert array lenght: ";
  std::size_t n;
  std::cin >> n;
  int* da{new int[n]};  // allocated on the HEAP, or free-store
                        //new is similar to malloc (but there are differences)

  for (std::size_t i{0}; i < n; ++i)
    da[i] = i * 10;

  for (std::size_t i{0}; i < n; ++i)
    std::cout << "da[" << i << "] = " << da[i] << std::endl;

  delete[] da;  //we must delete dynamic array!!!
                //heap is not automatically dealocated (like java with garbage collector)
  return 0;
}
