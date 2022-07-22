#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void print_vector(vector<T>& vector) {
	for(auto item : vector) {
		cout << item << " ";
	}
	cout << endl;
}

vector<int> generate_vector_of_prime_numbers() {
  vector<int> primes;
  primes.push_back(2);
	primes.push_back(3);
	primes.push_back(5);
	primes.push_back(7);
  for (int i{3}; i <= 100; ++i) {
    if ((i % 3 != 0) && (i % 2 != 0) && (i % 5 != 0) && (i % 7 != 0)) {
      primes.push_back(i);
    }
  }
  return primes;
}

int main() {
  vector<int> primes{generate_vector_of_prime_numbers()};
	print_vector(primes);
	return 0;
}