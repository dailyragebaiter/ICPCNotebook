#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005; // thay đổi theo n tối đa
const int MOD = 1e9 + 7; // hoặc 998244353

int C[MAXN][MAXN];

void buildCKN() {
    for (int n = 0; n < MAXN; n++) {
        C[n][0] = 1; // C(n,0) = 1
        for (int k = 1; k <= n; k++) {
            C[n][k] = (C[n-1][k-1] + C[n-1][k]) % MOD; // C(n,k) = C(n-1,k-1) + C(n-1,k)
        }
    }
}

int main() {
    buildCKN();
    // ví dụ: C(5,2)
    cout << C[5][2] << "\n"; // Output: 10
}