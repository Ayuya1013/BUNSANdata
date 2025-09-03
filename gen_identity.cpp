#include <vector>
#include <iostream>
#include <typeinfo>
std::vector<std::vector<double>> gen_identity(int n) {//整数nを受け取りn x n の単位行列を生成する関数
    if (typeid(n) != typeid(int) || n <= 0) {
        std::cerr << "n must be a positive integer" << std::endl;
        return {};
    }
    std::vector<std::vector<double>> identity_matrix(n, std::vector<double>(n, 0));
    for (int i = 0; i < n; ++i) {//対角成分を1に設定
        identity_matrix[i][i] = 1;
    }
    return identity_matrix;
}
int main() {
    int n;
    std::cout << "Enter the size of the identity matrix: ";
    std::cin >> n;
    std::vector<std::vector<double>> identity = gen_identity(n);
    for (const auto& row : identity) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}