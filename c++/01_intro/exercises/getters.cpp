#include <iostream>

void get_int() {
    int i;
    while(std::cin >> i) {
        if(i == 4) break;
        std::cin.clear();
    }
    std::cout << "Finish" << std::endl;
}

void get_double() {
    double i;
    while(std::cin >> i) {
        if(abs(i-4.0)<1e-15) break;
        std::cin.clear();
    }
    std::cout << "Finish" << std::endl;
}

int main() {
    
    get_int();
    get_double();
    return 0;
}