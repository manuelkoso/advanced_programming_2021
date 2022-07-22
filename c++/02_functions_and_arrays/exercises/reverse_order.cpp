#include <iostream>

using namespace std;

template <typename T>
T* create_array(size_t size) {
  T* array{new T[size]};

  for (int i = 0; i < size; i++) {
    cin >> array[i];
  }

  return array;
}

template <typename T>
void reverse_print_array(T* array, int size) {
  for (int i = size - 1; i >= 0; i = i - 1) {
    cout << array[i] << " ";
  }
  cout << endl;
}

int main() {
  size_t size_of_array;
  cin >> size_of_array;

  int* array = create_array<int>(size_of_array);

  reverse_print_array<int>(array, size_of_array);

  delete[] array;
}