#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ifstream file("temperatures.txt");

  vector<double> vector;
  double temp = 0;

  if (file.is_open()) {
    while (file >> temp) {
      vector.push_back(temp);
    }
    file.close();
  }

  double mean = 0;
  for (auto x : vector) {
    mean = mean + x;
  }

  mean = mean / vector.size();

  cout << "The mean is: " << mean << endl;

  sort(vector.begin(), vector.end());

  double median = 0;

  if (vector.size() % 2 == 1) {
    median = vector.at(vector.size() / 2);
  } else {
    median =
        (vector.at(vector.size() / 2) + vector.at((vector.size() / 2) - 1)) / 2;
  }

  cout << "The median is: " << median << endl;  

}