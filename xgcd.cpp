#include <iostream> 
int xgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = xgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

// int main() {
//     int a, b;
//     std::cout << "Enter two integers: ";
//     std::cin >> a >> b;
//     int x, y;
//     int gcd = xgcd(a, b, x, y);
//     std::cout << "GCD: " << gcd << ", x: " << x << ", y: " << y << std::endl;
//     return 0;
// }
