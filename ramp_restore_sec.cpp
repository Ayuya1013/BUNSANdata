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

std::vector<int> ramp_restore_sec(std::vector<std::pair<int, int>> &vk, int k, int L, std::vector<int> sidlist, int q) {
    std::vector<int> secrets;
    for (int l = 0; l < L; ++l) {
        int x = sidlist[l];
        int secret = 0;
        for (int j = 0; j < k; ++j) {
            int xj = vk[j].first;
            int yj = vk[j].second;
            int lambda = lagrange_lambda(vk, j, x, q);
            if (lambda == -1) return std::vector<int>(L, -1);
            secret = (secret + yj * lambda) % q;
        }
        secrets.push_back((secret + q) % q);
    }
    return secrets;
}


int main() {
    std::vector<std::pair<int, int>> vk = {
        {1, 12341596},
        {2, 2755276},
        {3, 7112885},
        {4, 560058},
        {5, 14384099}
    };
    int L = 5;// 復元したい秘密の数
    std::vector<int> sidlist = {21, 22, 23, 24, 25};
    int k = 5;// 閾値
    int q = 16777213;

    std::vector<int> secrets = ramp_restore_sec(vk, k, L, sidlist, q);
    if (secrets[0] != -1) {
        for (int i = 0; i < secrets.size(); ++i) {
            std::cout << "復元された秘密[" << i << "] = " << secrets[i] << std::endl;
        }
    } else {
        std::cout << "秘密の復元に失敗しました" << std::endl;
    }
    return 0;
}
