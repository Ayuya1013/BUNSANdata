#include <iostream>
#include <vector> 
std::vector<std::vector<int>> gen_identity(int n) {//整数nを受け取りn x n の単位行列を生成する関数
    if (typeid(n) != typeid(int) || n <= 0) {
        std::cerr << "n must be a positive integer" << std::endl;
        return {};
    }
    std::vector<std::vector<int>> identity_matrix(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {//対角成分を1に設定
        identity_matrix[i][i] = 1;
    }
    return identity_matrix;
}
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
std::vector<std::vector<int>> mat_inverse_mod(std::vector<std::vector<int>> A, int mod) {
    int n = A.size();
    int q = mod;
    std::vector<std::vector<int>> I = gen_identity(n);
    for (int i = 0; i < n; ++i) {
        // ピボット選択と逆元
        if (A[i][i] == 0) {
            bool swapped = false;
            for (int k = i + 1; k < n; ++k) {
                if (A[k][i] != 0) {
                    std::swap(A[i], A[k]);
                    std::swap(I[i], I[k]);
                    swapped = true;
                    break;
                }
            }
            if (!swapped) throw std::runtime_error("逆行列が存在しません");
        }

        int pivot_inv = inv_mod(A[i][i], q);
        for (int j = 0; j < n; ++j) {
            A[i][j] = A[i][j] * pivot_inv % q;
            I[i][j] = I[i][j] * pivot_inv % q;
        }

        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            int factor = A[k][i];
            for (int j = 0; j < n; ++j) {
                A[k][j] = (A[k][j] - factor * A[i][j]) % q;
                if (A[k][j] < 0) A[k][j] += q;
                I[k][j] = (I[k][j] - factor * I[i][j]) % q;
                if (I[k][j] < 0) I[k][j] += q;
            }
        }
    }

    return I;
}

int main() {
    std::vector<std::vector<int>> A = {
        {1,2},
        {3,4}
    };
    int mod = 5;

    try {
        auto inv = mat_inverse_mod(A, mod);
        std::cout << "Inverse matrix mod " << mod << ":" << std::endl;
        for (const auto& row : inv) {
            std::cout << "[ ";
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << "]" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
