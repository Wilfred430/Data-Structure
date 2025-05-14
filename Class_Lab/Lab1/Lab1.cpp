#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 大數長除法
vector<int> divideLargeNumber(vector<int>& number, int divisor) {
    vector<int> result;
    int remainder = 0;

    for (int i = number.size() - 1; i >= 0; i--) {
        int currentDigit = remainder * 10 + number[i];
        result.push_back(currentDigit / divisor);
        remainder = currentDigit % divisor;
    }

    // 反轉結果回到正確的順序
    reverse(result.begin(), result.end());

    // 移除前導零
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

// 大數減法
vector<int> subtractLargeNumbers(vector<int>& a, vector<int>& b) {
    vector<int> result;
    int borrow = 0;

    for (size_t i = 0; i < a.size(); i++) {
        int digitA = a[i];
        int digitB = (i < b.size()) ? b[i] : 0;
        int diff = digitA - digitB - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.push_back(diff);
    }

    // 移除前導零
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

// 比較兩個大數的大小 (返回 true 表示 N > M)
bool Compare(vector<int>& N, vector<int>& M) {
    if (N.size() != M.size()) {
        return N.size() > M.size();
    }
    for (int i = N.size() - 1; i >= 0; i--) {
        if (N[i] != M[i]) {
            return N[i] > M[i];
        }
    }
    return false; // 相等時返回 false
}

int main() {
    string n1, n2;
    while (cin >> n1 >> n2) {
        vector<int> N, M;

        // 轉換字串為倒序 vector<int> 表示大數
        for (int i = n1.length() - 1; i >= 0; i--) {
            N.push_back(n1[i] - '0');
        }
        for (int i = n2.length() - 1; i >= 0; i--) {
            M.push_back(n2[i] - '0');
        }

        int ans = 1;
        while ((N.size() != 1 || N[0] != 0) && (M.size() != 1 || M[0] != 0)) {
            if (N[0] % 2 == 0 && M[0] % 2 == 0) {
                ans *= 2;
                N = divideLargeNumber(N, 2);
                M = divideLargeNumber(M, 2);
            } else if (N[0] % 2 == 0) {
                N = divideLargeNumber(N, 2);
            } else if (M[0] % 2 == 0) {
                M = divideLargeNumber(M, 2);
            }

            if (Compare(N, M)) {
                swap(N, M);
            }
            M = subtractLargeNumbers(M, N);
        }

        // 最終輸出 GCD 乘上 ans
        vector<int> GCD = (N.size() == 1 && N[0] == 0) ? M : N;

        // GCD * ans (這部分要手動相乘)
        vector<int> finalResult;
        int carry = 0;
        for (size_t i = 0; i < GCD.size(); i++) {
            int product = GCD[i] * ans + carry;
            finalResult.push_back(product % 10);
            carry = product / 10;
        }
        while (carry) {
            finalResult.push_back(carry % 10);
            carry /= 10;
        }

        // 反轉輸出
        for (int i = finalResult.size() - 1; i >= 0; i--) {
            cout << finalResult[i];
        }
        cout << endl;
    }

    return 0;
}
