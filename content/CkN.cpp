#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 1e9 + 7;
const int N = 1e6 + 5;

int gt[N];

void prepare() {
    gt[0] = 1;
    for (int i = 1 ; i <= 1e6 ; i ++) {
        gt[i] = gt[i - 1] * i % mod;
    }
}

int mul (int a, int b) {
    if (b == 0) {
        return 0;
    }
    int t = mul (a, b / 2);
    t = (t + t) % mod;
    if (b % 2 == 1) {
        t = (t + a) % mod;
    }
    return t;
}

int power (int a, int b) {
    if (b == 0) {
        return 1;
    }
    int t = power (a, b / 2);
    t = (t * t) % mod;
    if (b % 2 == 1) {
        t = (t * a) % mod;
    }
    return t;
}

int inversion (int a) {
    return power (a, mod - 2);
}

int C (int n, int k) {
    if (k > n) return 0;
    return ((gt[n] * inversion(gt[k]) % mod) * inversion(gt[n - k])) % mod;
}

signed main() {
    ios_base::sync_with_stdio (0);
    cin.tie (0);
    prepare();
    int n, q, k;
    cin >> q;
    while (q --) {
        cin >> n >> k;
        cout << C (n, k) << '\n';
    }
}