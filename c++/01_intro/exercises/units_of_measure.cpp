#include <iostream>

int main() {
    
    double value;
    std::string measure;

    std::cin >> value;
    std::cin >> measure;

    if(measure.compare("inch") == 0) {
        std::cout << value*0.0254 << " m" << std::endl;
    }

    return 0;
}