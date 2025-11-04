#include <bits/stdc++.h>
using namespace std;
#define int long long
int st[100005 * 6];
int lazy[100005 * 6];
int a[100005 * 6];
struct Node {
    int lazy;
    int val;
};
Node nodes[100005 * 4];

void down(int id) {
    int t = nodes[id].lazy;
    nodes[id*2].lazy += t;
    nodes[id*2].val += t;

    nodes[id*2+1].lazy += t;
    nodes[id*2+1].val += t;

    nodes[id].lazy = 0;
}

void update(int id, int l, int r, int u, int v, int val) {
    if (v < l || r < u) {
        return ;
    }
    if (u <= l && r <= v) {
        nodes[id].val += val;
        nodes[id].lazy += val;
        return ;
    }
    int mid = (l + r) / 2;

    down(id);

    update(id * 2, l, mid, u, v, val);
    update(id * 2 + 1, mid + 1, r, u, v, val);

    nodes[id].val = min(nodes[id*2].val, nodes[id*2+1].val);
}

int get(int id, int l, int r, int u, int v) {
    if (v < l || r < u) {
        return 1e18;
    }
    if (u <= l && r <= v) {
        return nodes[id].val;
    }
    int mid = (l + r) / 2;
    down(id);

    return min(get(id*2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}

signed main() {
    int n, x, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        update (1, 1, n, i, i, a[i]);
    }
    while (q --){
        int type, l, r, val;
        cin >> type;
        if (type == 1) {
            cin >> l >> r >> val;
            update(1, 1, n, l, r, val);
        }
        if (type == 2){
            cin >> l >> r;
            cout << get(1, 1, n, l, r) << '\n';
        }
    }
}