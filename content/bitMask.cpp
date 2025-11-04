#include <bits/stdc++.h>
using namespace std;

const int N = 22;
const int inf = 1e9 + 7;

int a[N][N], f[N][1 << 21];

bool bit (int n, int i) {
    return ((n >> i) & 1);
}

int flip (int n, int i) {
    return n ^ (1 << i);
}

int n;

int dp (int i, int mask) {
    if (mask == (1 << n) - 1) {
        return a[i][1];
    }
    if (f[i][mask] != -1) {
        return f[i][mask];
    }
    int res = inf;
    for (int j = 1; j <= n; j ++) {
        if (bit (mask, j - 1) == 0) {
            res = min (res, dp (j, flip (mask, j - 1)) + a[i][j]);
        }
    }
    //cout << f[i][mask] << " " << i << " " << mask << '\n';
    return f[i][mask] = res;
}

int main () {
    ios_base :: sync_with_stdio (0);
    cin.tie (0);
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cin >> a[i][j];
        }
    }
    memset (f, -1, sizeof (f));
    cout << dp (1, 0);
}