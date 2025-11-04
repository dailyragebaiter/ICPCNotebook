#include <bits/stdc++.h>

#define task   "BriantheCrab"

#define ll     long long
#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())

using namespace std;

template <class T> void mini (T &t, T f) {if (t > f) t = f;}
template <class T> void maxi (T &t, T f) {if (t < f) t = f;}

const int maxN = 1e5 + 5;
const int inf = 1e9 + 7;
const int mod = 1e9 + 7;

struct ST {
    pii st[maxN * 4];
    
    ST () {
        for (int i = 0; i < maxN * 4; i ++) {
            st[i] = {-inf, inf};
        }
    }
    
    void Upd (int id, int l, int r, int pos, int val) {
        if (pos < l || pos > r) {
            return;
        }
        if (l == r) {
            st[id] = {val, val};
            return; 
        }
        int mid = (l + r) >> 1;
        Upd (id * 2, l, mid, pos, val);
        Upd (id * 2 + 1, mid + 1, r, pos, val);
        int tMax = max (st[id * 2].fi, st[id * 2 + 1].fi);
        int tMin = min (st[id * 2].se, st[id * 2 + 1].se);
        st[id] = {tMax, tMin};
        return;
    }
    
    pii Get (int id, int l, int r, int u, int v) {
        if (u > r || v < l) {
            return {-inf, inf};
        }
        if (u <= l && r <= v) {
            return st[id];
        }
        int mid = (l + r) >> 1;
        auto tL = Get (id * 2, l, mid, u, v);
        auto tR = Get (id * 2 + 1, mid + 1, r, u, v);
        return {max (tL.fi, tR.fi), min (tL.se, tR.se)};
    }
};

struct edge {
    int u, v, w;
};

int n, a[maxN];
int sz[maxN], par[maxN], head[maxN], h[maxN];
int nodeId[maxN], pos[maxN], cnt = 0;
vector <int> adj[maxN];
vector <edge> all;
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

int LCA (int u, int v) {
    while (head[u] != head[v]) {
        if (sz[head[u]] < sz[head[v]]) {
            u = par[head[u]];
        }
        else {
            v = par[head[v]];
        }
    }
    return ((sz[u] > sz[v]) ? u : v);
}

pii query (int u, int v) {
    int res1 = 0, res2 = inf;
    int lca = LCA (u, v);
    while (head[u] != head[v]) {
        if (h[head[u]] < h[head[v]]) {
            swap (u, v);
        }
        pii tmp = T.Get (1, 1, n, pos[head[u]] + (head[u] == lca), pos[u]);
        maxi (res1, tmp.fi);
        mini (res2, tmp.se);
        u = par[head[u]];
    }
    if (h[u] > h[v]) {
        swap (u, v);
    }
    pii tmp = T.Get (1, 1, n, pos[u] + (u == lca), pos[v]);
    maxi (res1, tmp.fi);
    mini (res2, tmp.se);
    return {res1, res2};
}

void Solve () {
    cin >> n;
    for (int i = 1; i <= n - 1; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        all.push_back ({u, v, w});
        adj[u].push_back (v);
        adj[v].push_back (u);
    }
    dfs (1, 1);
    HLD (1, 1, 1);
    for (auto [u, v, w] : all) {
        if (pos[u] < pos[v]) {
            swap (u, v);
        }
        T.Upd (1, 1, n, pos[u], w);
    }
    int q;
    cin >> q;
    //cout << q << '\n';
    while (q --) {
        int u, v;
        cin >> u >> v;
        auto [mx, mi] = query (u, v);
        cout << mi << ' ' << mx << '\n';
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
