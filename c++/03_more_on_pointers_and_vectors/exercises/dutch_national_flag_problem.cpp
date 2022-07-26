#include <iostream>
#include <vector>

// https://en.wikipedia.org/wiki/Dutch_national_flag_problem

using namespace std;

template <typename T>
void swap(vector<T>& vector, int i, int j) {
    T tmp = vector.at(i);
    vector.at(i) = vector.at(j);
    vector.at(j) = tmp;
}

template <typename T>
void dutch_algorithm(vector<T>& vector, int value) {

    int i = 0;  
    int lower_index = 0;
    int higher_index = vector.size() - 1;

    while(i <= higher_index) {
        if(vector.at(i) < value) {
            swap(vector, i, lower_index);
            ++lower_index;
            ++i; 
        } else if(vector.at(i) > value) {
            swap(vector, i, higher_index);
            --higher_index;
        } else {
            ++i;
        }
    }
    
}

int main() {
  vector<int> vector = {1, 5, 6, 5, 5, 3, 4};
  int value;
  cin >> value;

  cout << "Initial array" << endl;
  for (auto x : vector)
    cout << x;

  cout << endl;

  cout << "Dutch algorithm" << endl;

  dutch_algorithm(vector, value);

  for (auto x : vector)
    cout << x;

  cout << endl;
  return 0;
}