#include <vector>
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

int lagrange_lambda(std::vector<std::pair<int, int>> &vk, int j, int x, int q) {
    int result = 1;
    
    for (int m = 0; m < vk.size(); ++m) {
        if (m != j) {
            result = (result * (x - vk[m].first)) % q;//分子
            int denom = (vk[j].first - vk[m].first) % q;//分母
            if (denom < 0) denom += q;//負の数を正に変換
            int inv_denom = 1;//denomの逆元
            // 拡張ユークリッドの互除法で逆元を求める
            inv_denom = inv_mod(denom, q);
            if (inv_denom == -1) {
                // 逆元が存在しない場合の処理（必要に応じてエラーハンドリングを追加）
                return -1; // ここでは-1を返す
            }
            result = (result * inv_denom) % q;//分子*逆元   
        }
    }
    return result; // 最終的な結果
}

// int main() {
//     std::vector<std::pair<int, int>> vk = {
//         {1, 2},
//         {2, 4},
//         {3, 8}
//     };
//     int j = 1;       // vk[1] = (2, 4)
//     int x = 5;       // 補間したい点
//     int q = 17;      // 法（素数）

//     int lambda = lagrange_lambda(vk, j, x, q);
//     if (lambda != -1) {
//         std::cout << "λ_" << j << "(x=" << x << ") ≡ " << lambda << " mod " << q << std::endl;
//     } else {
//         std::cout << "逆元が存在しないため λ_" << j << " は計算できません" << std::endl;
//     }

//     return 0;
// }