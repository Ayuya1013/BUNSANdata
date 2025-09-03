#include <iostream>

int xgcd(int a, int b, int &x, int &y) {//拡張ユークリッドの互除法
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

int inv_mod(int a, int m) {//aのmにおける逆元を求める
    int x, y;
    if(xgcd(a, m, x, y) != 1) {
        return -1; //逆元が存在しない
    } else {
        return (x % m + m) % m; //xは逆元の法の整数倍となるので0<x<mに変換
    }
}

int main() {
    int a, m;
    std::cout << "Enter two integers (a m): ";
    std::cin >> a >> m;
    int inv = inv_mod(a, m);
    if (inv == -1) {
        std::cout << "Inverse does not exist." << std::endl;
    } else {
        std::cout << "Inverse: " << inv << std::endl;
    }
    return 0;
}