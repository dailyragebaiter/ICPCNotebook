#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 5;
const int inf = 1e18 + 7;

struct data {
    int sum, prefix, suffix, best;
};

int n, m, a[N];
data st[N * 4];

data combine (data l, data r) {
    data res;
    res.sum = l.sum + r.sum;
    res.suffix = max (r.suffix, r.sum + l.suffix);
    res.prefix = max (l.prefix, l.sum + r.prefix);
    res.best = max ({l.best, r.best, l.suffix + r.prefix});
    return res;
}

void build (int id, int l, int r) {
    if (l == r) {
        st[id] = {a[l], a[l], a[l], a[l]};
        return ;
    }
    int mid = (l + r) / 2;
    build (id * 2, l, mid);
    build (id * 2 + 1, mid + 1, r);
    st[id] = combine (st[id * 2], st[id * 2 + 1]);
}

void update (int id, int l, int r, int i, int v) {
    if (i < l || i > r) {
        return ;
    }
    if (l == r) {
        st[id] = {v, v, v, v};
        return ;
    }
    int mid = (l + r) / 2;
    update (id * 2, l, mid, i, v);
    update (id * 2 + 1, mid + 1, r, i, v);
    st[id] = combine (st[id * 2], st[id * 2 + 1]);
}

data get (int id, int l, int r, int u, int v) {
    if (r < u || l > v) {
        return {0LL, -inf, -inf, -inf};
    }
    if (u <= l && r <= v) {
        return st[id];
    }
    int mid = (l + r) / 2;
    return combine (get (id * 2, l, mid, u, v), get (id * 2 + 1, mid + 1, r, u, v));
}

signed main () {
    ios_base :: sync_with_stdio (0);
    cin.tie (0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    build (1, 1, n);
    cin >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        cout << get (1, 1, n, u, v).best << '\n';
    }
    return 0;
}