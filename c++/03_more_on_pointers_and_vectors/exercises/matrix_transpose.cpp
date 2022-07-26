#include <array>
#include <iostream>

using namespace std;

template <typename T, size_t N>
void print_matrix(const array<T, N>& array, const int rows, const int cols) {
  for (int i = 0; i < array.size(); ++i) {
    if (i % cols == 0) {
      cout << "\n";
    }
    cout << array.at(i) << " ";
  }
  cout << endl;
}

template <typename T, size_t N>
void transpose(array<T, N>& matrix,
               const int number_rows,
               const int number_cols) {
  array<T, N> transpose;
  int index = 0;
  for (int i = 0; i < number_cols; ++i) {
    for (int j = i; j < matrix.size(); j = j + number_cols) {
      transpose.at(index) = matrix.at(j);
      ++index;
    }
  }

  matrix.swap(transpose);
}

int main() {
  const int number_rows = 3;
  const int number_cols = 2;

  array<double, number_rows* number_cols> matrix = {1, 2, 3, 4, 5, 6};

  print_matrix(matrix, number_rows, number_cols);

  transpose(matrix, number_rows, number_cols);

  print_matrix(matrix, number_cols, number_rows);

  return 0;
}