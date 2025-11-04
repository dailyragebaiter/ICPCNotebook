#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 5;

vector<int> adj[N];
int m = 0, root = 1;
int tour[2 * N], en[N], st[N], delta[2 * N], result[N];
int n, q;

struct fenwick {
    int bit[N];
    fenwick () {
        memset (bit, 0, sizeof (bit));
    }
 
    void update (int x, int val) {
        for (; x <= n; x += x & - x) {
            bit[x] += val;
        }
    }
 
    int get (int x) {
        int ans = 0;
        for (; x > 0; x -= x & - x) {
            ans += bit[x];
        }
        return ans;
    }
} T;

void dfs(int u, int parent_of_u) {
    st[u] = ++m;
    tour[m] = u;
    for (int v : adj[u]) {
        if (v != parent_of_u) {
            dfs(v, u);
        }
    }
    en[u] = m;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    int u, v, x;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(root, 0);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v;
            cin >> u >> v;
            T.update (st[u], v);
            T.update (en[u] + 1, -v);
        }
        if (type == 2) {
            int u;
            cin >> u;
            cout << T.get (st[u]) << '\n';
        }
        
    }
    return 0;
}