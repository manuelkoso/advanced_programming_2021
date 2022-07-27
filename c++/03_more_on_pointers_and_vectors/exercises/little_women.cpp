#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void vector_version() {
  string word;
  vector<string> words;
  vector<int> counter_words;

  ifstream file("LittleWomen.txt");
  if (file.is_open()) {
    while (file >> word) {
      words.push_back(word);
    }
    file.close();
  }

  for (auto x : words) {
    int counter = 0;
    for (auto y : words) {
      if (x.compare(y)) {
        ++counter;
      }
    }
    cout << x << " " << counter << "\n";
  }
  cout << endl;
}

void map_version() {
  string word;
  int debug_counter = 0;
  map<string, int> words;
  ifstream file("LittleWomen.txt");
  if (file.is_open()) {
    while (file >> word) {
      ++words[word];
      ++debug_counter;
    }
    cout << "\n";
    file.close();
  }

  for (pair<string, int> item : words) {
    cout << item.first << " : " << item.second << " ";
  }
  cout << endl;
}

void unordered_map_version() {
  string word;
  unordered_map<string, int> words;
  ifstream file("LittleWomen.txt");
  if (file.is_open()) {
    while (file >> word) {
      ++words[word];
    }
    file.close();
  }

  for (pair<string, int> item : words) {
    cout << item.first << " : " << item.second << " ";
  }
  cout << endl;

}

int main() {
  /* {
    cout << "Vector version" << endl;
    auto t0 = chrono::high_resolution_clock::now();
    vector_version();
    auto t1 = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(t1 - t0);
    cout << "Elapsed " << elapsed.count() << " [milliseconds]" << endl;
  } */

  {
    cout << "Map version" << endl;
    auto t0 = chrono::high_resolution_clock::now();
    map_version();
    auto t1 = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(t1 - t0);
    cout << "Elapsed " << elapsed.count() << " [milliseconds]" << endl;
  }

  {
    cout << "Unordered map version" << endl;
    auto t0 = chrono::high_resolution_clock::now();
    unordered_map_version();
    auto t1 = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(t1 - t0);
    cout << "Elapsed " << elapsed.count() << " [milliseconds]" << endl;
  }
}
