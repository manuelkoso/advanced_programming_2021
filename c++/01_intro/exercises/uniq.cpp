#include <iostream>
#include <map>

using namespace std;

int main() {
  
  map<string, int> line_counter;

  string line;
  while (getline(cin, line)) {
    ++line_counter[line];
  }

  for(const auto& x: line_counter) {
    cout << x.first << " " << x.second << "\n";
  }
  cout << endl;

    return 0;

}