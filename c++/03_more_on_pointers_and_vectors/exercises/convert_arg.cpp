#include <vector>
#include <iostream>

using namespace std;

template <typename T>
void print_matrix(const vector<T>& matrix, const int rows, const int cols) {
  for (int i = 0; i < matrix.size(); ++i) {
    if (i % cols == 0) {
      cout << "\n";
    }
    cout << matrix.at(i) << " ";
  }
  cout << endl;
}

template <typename T>
void transpose(vector<T>& matrix,
               const int number_rows,
               const int number_cols) {
  vector<T> transpose;
  for (int i = 0; i < number_cols; ++i) {
    for (int j = i; j < matrix.size(); j = j + number_cols) {
      transpose.push_back(matrix.at(j));
    }
  }

  matrix.swap(transpose);
}

struct Argument_invalid {
  string message;
  Argument_invalid(string s) : message{move(s)} {}
  const char* what() const { return message.c_str(); }
};

int main(int argc, char* argv[]) {
  
  int number_rows = 0;
  int number_cols = 0;

  try {
    if (argc < 3) {
      throw Argument_invalid{"You have to specify the number of rows and number of cols"};
    } else {
      size_t pos;
      number_rows = stoi(argv[1], &pos);
      number_cols = stoi(argv[2], &pos);
    }
  } catch (Argument_invalid e) {
    cerr << e.what() << endl;
  }

  vector<double> matrix;

  for (int i = 0; i < number_rows*number_cols; ++i) {
    int tmp;
    cin >> tmp; 
    matrix.push_back(tmp);
  }

  print_matrix(matrix, number_rows, number_cols);

  transpose(matrix, number_rows, number_cols);

  print_matrix(matrix, number_cols, number_rows);

  return 0;
}