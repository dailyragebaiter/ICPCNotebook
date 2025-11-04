#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector <int> st[N * 4];
int a[N];

void build (int id, int l, int r) {
    if (l == r) {
        st[id].push_back (a[l]);
        return ;
    }
    int mid = (l + r) / 2;
    build (id * 2, l, mid);
    build (id * 2 + 1, mid + 1, r);
    st[id].resize(st[id * 2].size() + st[id * 2 + 1].size());
    merge (st[id * 2].begin (), st[id * 2].end (), st[id * 2 + 1].begin (), st[id * 2 + 1].end (), st[id].begin ());
}

void update (int id, int l, int r, int i, int v) {
    if (i < l || i > r) {
        return ;
    }
    if (l == r) {
        st[id].push_back (v);
        return ;
    }
    update (id * 2, l, (l + r) / 2, i, v);
    update (id * 2 + 1, (l + r) / 2 + 1, r, i, v);
    st[id].resize(st[id * 2].size() + st[id * 2 + 1].size());
    merge (st[id * 2].begin (), st[id * 2].end (), st[id * 2 + 1].begin (), st[id * 2 + 1].end (), st[id].begin ());
}

int get (int id, int l, int r, int u, int v, int k) {
    if (v < l || r < u) {
        return 0;
    }
    if (u <= l && r <= v) {
        int val = upper_bound (st[id].begin (), st[id].end (), k) - st[id].begin ();
        return (st[id].size () - val);
    }
    int mid = (l + r) / 2;
    return get (id * 2, l, mid, u, v, k) + get (id * 2 + 1, mid + 1, r, u, v, k);
}

int main () {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        //update (1, 1, n, i, a[i]);
    }
    build (1, 1, n);
    while (q --) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << get (1, 1, n, l, r, k) << '\n';
    }
}