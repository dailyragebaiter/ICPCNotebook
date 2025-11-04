#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;

int st[400020]; 
int a[100005];

void build(int id, int l, int r) {
    if (l == r) {
        st[id] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = min(st[id * 2], st[id * 2 + 1]);
}

void update(int id, int l, int r, int i, int v) {
    if (i < l || r < i) {
        return;
    }
    if (l == r) {
        a[i] += v;  
        st[id] = a[i];
        return;
    }
    int mid = (l + r) / 2;
    update(id * 2, l, mid, i, v);
    update(id * 2 + 1, mid + 1, r, i, v);
    st[id] = min(st[id * 2], st[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v) {
    if (r < u || v < l) {
        return INF;
    }
    if (u <= l && r <= v) {
        return st[id];
    }
    int mid = (l + r) / 2;
    return min(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build(1, 1, n);

    for (int i = 1; i <= m; i++) {
        int k, x, y;
        cin >> k >> x >> y;
        if (k == 1) {
            update(1, 1, n, x, y);
        } else if (k == 2) {
            cout << get(1, 1, n, x, y) << '\n';
        }
    }

    return 0;
}