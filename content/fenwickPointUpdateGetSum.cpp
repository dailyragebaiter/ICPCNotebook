#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 5;

int a[N], n;

struct fenwick {
    int bit[N];
    
    fenwick () {
        memset (bit, 0, sizeof (bit));
    }
    
    void update (int x, int val) {
        for (; x <= n; x += x & -x) {
            bit[x] += val;
        }
    }
    
    int get (int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) {
            res += bit[x];
        }
        return res;
    }
} T;

signed main () {
    int q;
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        T. update (i, a[i]);
    }
    while (q --) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1) {
            T.update (u, -a[u] + v);
            a[u] = v;
        }
        else {
            cout << T.get (v) - T.get (u - 1) << '\n';
        }
    }
}