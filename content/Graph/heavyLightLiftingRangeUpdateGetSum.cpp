#include <bits/stdc++.h>
 
#define task   "BriantheCrab"
 
#define int    long long
#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())
 
using namespace std;
 
template <class T> void mini (T &t, T f) {if (t > f) t = f;}
template <class T> void maxi (T &t, T f) {if (t < f) t = f;}
 
const int maxN = 2e5 + 5;
const int inf = 1e9 + 7;
const int mod = 1e9 + 7;
 
struct ST {
    int st[maxN * 4];
    
    ST () {
        memset (st, 0, szf (st));
    }
    
    void Upd (int id, int l, int r, int pos, int val) {
        if (pos < l || pos > r) {
            return;
        }
        if (l == r) {
            st[id] = val;
            return; 
        }
        int mid = (l + r) >> 1;
        Upd (id * 2, l, mid, pos, val);
        Upd (id * 2 + 1, mid + 1, r, pos, val);
        st[id] = st[id * 2] + st[id * 2 + 1];
        return;
    }
    
    int Get (int id, int l, int r, int u, int v) {
        if (u > r || v < l) {
            return 0;
        }
        if (u <= l && r <= v) {
            return st[id];
        }
        int mid = (l + r) >> 1;
        int tL = Get (id * 2, l, mid, u, v);
        int tR = Get (id * 2 + 1, mid + 1, r, u, v);
        return (tL + tR);
    }
};
 
int n, a[maxN];
int sz[maxN], par[maxN], head[maxN], h[maxN];
int nodeId[maxN], pos[maxN], cnt = 0;
vector <int> adj[maxN];
ST T;
 
void dfs (int u, int p) {
    sz[u] = 1;
    par[u] = p;
    for (auto v : adj[u]) {
        if (v == p) {
            continue;
        }
        h[v] = h[u] + 1;
        dfs (v, u);
        sz[u] += sz[v];
    }
}
 
void HLD (int u, int h, int p) {
    head[u] = h;
    pos[u] = ++cnt;
    nodeId[cnt] = u;
    if (adj[u].size () == 1 && u != 1) {
        return;
    }
    int nxt = 0, curMax = 0;
    for (auto v : adj[u]) {
        if (v == p) {
            continue;
        }
        if (sz[v] > curMax) {
            curMax = sz[v];
            nxt = v;
        }
    }
    HLD (nxt, h, u);
    for (auto v : adj[u]) {
        if (v != nxt && v != p) {
            HLD (v, v, u);
        }
    }
}
 
int query (int u, int v) {
    int res = 0;
    while (head[u] != head[v]) {
        if (h[head[u]] < h[head[v]]) {
            swap (u, v);
        }
        res += T.Get (1, 1, n, pos[head[u]], pos[u]);
        u = par[head[u]];
    }
    if (h[u] > h[v]) {
        swap (u, v);
    }
    res += T.Get (1, 1, n, pos[u], pos[v]);
    return res;
}
 
void Solve () {
    int q;
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n - 1; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
        adj[v].push_back (u);
    }
    dfs (1, 1);
    HLD (1, 1, 1);
    for (int i = 1; i <= n; i ++) {
        T.Upd (1, 1, n, pos[i], a[i]);
    }
    while (q --) {
        int t;
        cin >> t;
        if (t == 1) {
            int s, x;
            cin >> s >> x;
            T.Upd (1, 1, n, pos[s], x);
        }
        else {
            int x;
            cin >> x;
            cout << query (1, x) << '\n';
        }
    }
    return;
}
 
signed main () {
    cin.tie (nullptr) -> sync_with_stdio (false);
    if (fopen (task".inp", "r")) {
        freopen (task".inp", "r", stdin);
        freopen (task".out", "w", stdout);
    }
    int t = 1;
    //cin >> t;
    while (t --) {
        Solve ();
    } 
    return 0;
}
// Belligerent :)