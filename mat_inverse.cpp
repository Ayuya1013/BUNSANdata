#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>

std::vector<std::vector<double>> gen_identity(int n) {
    std::vector<std::vector<double>> identity_matrix(n, std::vector<double>(n, 0));
    for (int i = 0; i < n; ++i) {
        identity_matrix[i][i] = 1;
    }
    return identity_matrix;
}

std::vector<std::vector<double>> mat_inverse(std::vector<std::vector<double>> A) {
    if (A.size() != A[0].size()) {
        throw std::invalid_argument("Matrix must be square");
    }

    int n = A.size();
    std::vector<std::vector<double>> I = gen_identity(n);

    for (int i = 0; i < n; ++i) {
        // ピボット選択
        double max_val = std::abs(A[i][i]);
        int max_row = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(A[k][i]) > max_val) {
                max_val = std::abs(A[k][i]);
                max_row = k;
            }
        }

        if (max_val == 0.0) {
            throw std::runtime_error("Matrix is singular and cannot be inverted");
            return {};
        }

        // 行の入れ替え
        if (i != max_row) {
            std::swap(A[i], A[max_row]);
            std::swap(I[i], I[max_row]);
        }

        // ピボット行の正規化
        double pivot = A[i][i];
        for (int j = 0; j < n; ++j) {
            A[i][j] /= pivot;
            I[i][j] /= pivot;
        }

        // 他の行からピボット列を消去
        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = A[k][i];
            for (int j = 0; j < n; ++j) {
                A[k][j] -= factor * A[i][j];
                I[k][j] -= factor * I[i][j];
            }
        }
    }

    return I;
}

int main() {
    std::vector<std::vector<double>> A = {//テストデータ
        {20, -10, 4, -1},
        {-45, 25, -11, 3},
        {36, -21, 10, -3},
        {-10, 6, -3, 1}
    };

    try {
        auto inv = mat_inverse(A);
        std::cout << "Inverse matrix:" << std::endl;
    for (const auto& row : inv) {
    std::cout << "[ ";
    for (const auto& elem : row) {
        std::cout << elem << " ";
    }
    std::cout << "]" << std::endl;
    }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
