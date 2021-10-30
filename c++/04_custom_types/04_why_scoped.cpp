#include <iostream>

enum class month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

using namespace std;

int main() {
  cout << nov << endl;  //if I used a scope enum doesn't compile
  // cout << dec << endl;
  //doesn't compile, because there ambiguites
  //we have two simbols:
  //- dec: is a function of std
  //- dec: is a member of month
  //=> compilation error
  //don't use using namespace

  std::cout << static_cast<int>(month::nov) << '\n';

  return 0;
}
