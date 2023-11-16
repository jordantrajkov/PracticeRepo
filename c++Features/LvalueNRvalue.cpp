#include <iostream>
#include <utility>

void processValue(const int &x) {
    std::cout << "Processing const lvalue: " << x << std::endl;
}

void processValue(int &&x) {
    std::cout << "Processing rvalue: " << x << std::endl;
}

void processValue(const int &&x) {
    std::cout << "Processing const rvalue: " << x << std::endl;
}

int main() {
    int a = 42;
    const int b = 23;

    processValue(a);               // Calls the const lvalue version
    processValue(std::move(a));    // Calls the rvalue version using std::move

    processValue(b);               // Calls the const lvalue version
    processValue(std::move(b));    // Calls the const rvalue version using std::move

    return 0;

    
    

    //OUTPUT

    // Processing const lvalue: 42
    // Processing rvalue: 42
    // Processing const lvalue: 23
    // Processing const rvalue: 23


}
