#include <iostream>
#include <sstream>
#include <string_view>


int main() {
    std::stringstream s;
    s.str() = "1 2 3";
    s.seekp(0);
    
    for (int i = 0; i < 3; ++i) {
        int a;
        s >> a;
        std::cout << a << "\n";
    }
    
    return 0;
}

