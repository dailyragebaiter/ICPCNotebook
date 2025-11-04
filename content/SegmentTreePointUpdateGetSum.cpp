#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 5;

int st[N * 4];
int a[N];

void update (int id, int l, int r, int i, int v) {
    if (i < l || i > r) {
        return ;
    }
    if (l == r) {
        st[id] = v;
        return ;
    }
    update (id * 2, l, (l + r) / 2, i, v);
    update (id * 2 + 1, (l + r) / 2 + 1, r, i, v);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

int get (int id, int l, int r, int u, int v) {
    if (r < u || v < l) {
        return 0;
    }
    if (u <= l && r <= v) {
        return st[id];
    }
    return get (id * 2, l, (l + r) / 2, u, v) + get (id * 2 + 1, (l + r) / 2 + 1, r, u, v);
}

signed main () {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        update (1, 1, n, i, a[i]);
    }
    while (q --) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1) {
            update (1, 1, n, u, v);
        }
        else {
            cout << get (1, 1, n, u, v) << '\n';
        }
    }
}