#include <bits/stdc++.h>

#define int long long
#define pii pair <int, int>
#define fi first
#define se second
#define szf sizeof
#define sz(s) (int)((s).size())

using namespace std;

const int N = 1e5 + 5;
const int inf = 1e18 + 7;
const int LOG = 20;

int up[N][LOG];
int h[N];
vector <int> adj[N];

void dfs (int u, int p) {
    up[u][0] = p;
    for (int j = 1; j <= LOG - 1; j ++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }
    for (auto v : adj[u]) {
        if (v == p) {
            continue;
        }
        h[v] = h[u] + 1;
        dfs (v, u);
    }
}

int LCA (int u, int v) {
    if (h[u] < h[v]) {
        swap (u, v);
    }
    int k = h[u] - h[v];
    for (int j = 0; (1LL << j) <= k; j++) {
        if ((k >> j) & 1) {
            u = up[u][j];
        }
    }
    if (u == v) {
        return u;
    }
    for (int j = LOG - 1; j >= 0; j --) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

signed main () {
    ios_base :: sync_with_stdio (0);
    cin.tie (0);
    cout.tie (0);
    #define task "crab"
    if (fopen (task".inp", "r")) {
        freopen (task".inp", "r", stdin);
        freopen (task".out", "w", stdout);
    }
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n - 1; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
        adj[v].push_back (u);
    }
    h[1] = 0;
    dfs (1, 0);
    while (q --) {
        int u, v;
        cin >> u >> v;
        cout << LCA (u, v) << ' ';
    }
    return 0;
}
// Brian the Crab
// stkwa 10324