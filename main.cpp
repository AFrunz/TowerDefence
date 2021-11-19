#include <iostream>
#include <vector>
//#include "headers/Objects.hpp"

int main() {
    std::vector<int> a;
    for (auto it = a.begin(); it < a.end(); it++){
        std::cout << *it;
    }
    return 0;
}
