#include <iostream>
#include <fstream>
#include <exception>

using namespace std;

struct Argument_invalid {
  string message;
  Argument_invalid(string s) : message{move(s)} {}
  const char* what() const {return message.c_str();}
};

int main(int argc, char *argv[]) {

  int max_chars = 0;
  int char_counter = 0;
  string word;

  try {
    if(argc < 2) {
      throw Argument_invalid{"There must be an integer as argument"};
    } else {
      size_t pos;
      max_chars = stoi(argv[1] , &pos);
    }
  } catch(Argument_invalid e) {
    cerr << e.what() << endl;
  }

  ifstream input_file;
  ofstream output_file;
  input_file.open("text.txt");
  output_file.open("fromatted_text.txt");

  bool first_word = true;

  while ((input_file >> word)) {
    char_counter = char_counter + word.size();
    if(char_counter > max_chars) {
      if(first_word) {
        output_file << word;
        first_word = false;
      } else {
        output_file << "\n" << word;
      }
      char_counter = word.size();
    } else {
      output_file << word << " ";
    }
  }

  input_file.close();
  output_file.close();
  return 0;
}