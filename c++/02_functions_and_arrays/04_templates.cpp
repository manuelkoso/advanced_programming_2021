#include <iostream>

template <typename T>
T dwim(const T a, const T b);

template <typename T, typename S>
T dwim(const T a, const S b);

int main() {
  int a{5}, b{7};
  double c{3.332}, d{7.7};
  float e{23.4}, f{3.34e2};
  char g{'0'}, h{'6'};

  std::cout << dwim<int>(a, b) << '\n'
            << dwim(c, d) << '\n' //we can ommit the template, are deduced base on the argument
            << dwim<int, float>(a, f) << '\n'
            << dwim(e, f) << '\n'
            << dwim(g, h) << std::endl;
  return 0;
}

template <typename T> //have to repeat the declaration of template
T dwim(const T a, const T b) {
  return a + b;
}


template <typename T, typename S>
T dwim(const T a, const S b) {
  return a + b;
}
