struct Fenwick {
    int n;
    vector <int> bit;
    
    inline void init (int _n) {
        n = _n;
        bit.assign (n + 2, 0);
    }
    
    inline void upd (int id, int val) {
        for (; id <= n; id += id & (-id)) {
            bit[id] += val;
        }
    }
    
    inline int get (int id) {
        int res = 0;
        for (; id; id -= id & (-id)) {
            res += bit[id];
        }
        return res;
    }
};

struct Fire {
    int t, u, c, s;
};

struct Query {
    int type, time, node, id;
};

bool cmp (Query A, Query B) {
    if (A.time != B.time) {
        return A.time < B.time;
    }
    return A.type < B.type;
}

int n, m, q;
Fire a[maxN];
pii b[maxN];
vector <Query> qry;
vector <int> adj[maxN];
Fenwick T1[maxN], T2[maxN];
int sz[maxN], par[maxN], del[maxN];
int h[maxN];
int res[maxN];
int rtCen;

int dfsSz (int u, int p) {
    sz[u] = 1;
    for (auto v : adj[u]) {
        if (v == p || del[v]) {
            continue;
        }
        sz[u] += dfsSz (v, u);
    }
    return sz[u];
}

int findCen (int u, int p, int curSz) {
    for (auto v : adj[u]) {
        if (v == p || del[v]) {
            continue;
        }
        if (sz[v] * 2 > curSz) {
            return findCen (v, u, curSz);
        }
    }
    return u;
}

vector <int> comp;

void collect (int u, int p) {
    comp.push_back (u);
    for (auto v : adj[u]) {
        if (v == p || del[v]) {
            continue;
        }
        collect (v, u);
    }
}

vector <int> chainC[maxN];

void build (int u, int d, int lstC) {
    int curSz = dfsSz (u, u);
    int c = findCen (u, 0, curSz);
    if (lstC != 0) {
        par[c] = lstC;
    }
    else {
        par[c] = 0;
        rtCen = c;
    }
    comp.clear ();
    collect (c, 0);
    for (auto x : comp) {
        chainC[x].push_back (c);
    }
    del[c] = 1;
    for (auto v : adj[c]) {
        if (del[v]) {
            continue;
        }
        build (v, d + 1, c);
    }
}

int up[maxN][18];

void pre (int u, int p) {
    up[u][0] = p;
    for (int j = 1; j < 18; j ++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }
    for (auto v : adj[u]) {
        if (v == p) {
            continue;
        }
        h[v] = h[u] + 1;
        pre (v, u);
    }
}

inline int lca (int u, int v) {
    if (h[u] < h[v]) {
        swap (u, v);
    }
    int k = h[u] - h[v];
    for (int i = 17; i >= 0; i --) {
        if ((k >> i) & 1) {
            u = up[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 17; i >= 0; i --) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

inline int dist (int u, int v) {
    return h[u] + h[v] - 2 * h[lca (u, v)];
}

vector <int> zip1[maxN], zip2[maxN];

inline void FjumpUpd (int u, int curDis, int val) {
    for (int k = 0; k < sz (chainC[u]); k ++) {
        int p = chainC[u][k];
        int child = (k ? chainC[u][k - 1] : 0);
        int d1 = dist (p, u);
        if (curDis - d1 >= 0) {
            zip1[p].push_back (curDis - d1);
            if (child != 0) {
                zip2[child].push_back (curDis - d1);
            }
        }
    }
}

inline void FjumpGet (int u) {
    for (int k = 0; k < sz (chainC[u]); k ++) {
        int p = chainC[u][k];
        int child = (k ? chainC[u][k - 1] : 0);
        int d1 = dist (p, u);
        zip1[p].push_back (d1);
        if (child != 0) {
            zip2[child].push_back (d1);
        }
    }
}

inline void jumpUpd (int u, int curDis, int val) {
    for (int k = 0; k < sz (chainC[u]); k ++) {
        int p = chainC[u][k];
        int child = (k ? chainC[u][k - 1] : 0);
        int d1 = dist (p, u);
        if (curDis - d1 >= 0) {
            int x1 = lower_bound (all (zip1[p]), curDis - d1) - zip1[p].begin () + 1;
            T1[p].upd (x1, val);
            if (child != 0) {
                int x2 = lower_bound (all (zip2[child]), curDis - d1) - zip2[child].begin () + 1;
                T2[child].upd (x2, val);
            }
        }
    }
}

inline int jumpGet (int u) {
    int ans = 0;
    for (int k = 0; k < sz (chainC[u]); k ++) {
        int p = chainC[u][k];
        int child = (k ? chainC[u][k - 1] : 0);
        int d1 = dist (p, u);
        int x1 = lower_bound (all (zip1[p]), d1) - zip1[p].begin () + 1;
        ans += T1[p].get (T1[p].n) - T1[p].get (x1 - 1);
        if (child != 0) {
            int x2 = lower_bound (all (zip2[child]), d1) - zip2[child].begin () + 1;
            ans -= T2[child].get (T2[child].n) - T2[child].get (x2 - 1);
        }
    }
    return ans;
}

inline void Solve () {
    cin >> n >> m >> q;
    for (int i = 1; i <= n - 1; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
        adj[v].push_back (u);
    }
    for (int i = 1; i <= m; i ++) {
        int t, u, c, s;
        cin >> t >> u >> c >> s;
        a[i] = {t, u, c, s};
        qry.push_back ({0, t, u, i});
    }
    for (int i = 1; i <= q; i ++) {
        cin >> b[i].fi >> b[i].se;
        qry.push_back ({1, b[i].fi, b[i].se, i});
    }
    build (1, 0, 0);
    pre (1, 1);
    for (int u = 1; u <= n; u ++) {
        reverse (all (chainC[u]));
    }
    sort (all (qry), cmp);
    for (int i = 0; i < sz (qry); i ++) {
        auto [type, time, node, id] = qry[i];
        if (type == 0) {
            FjumpUpd (node, a[id].s, a[id].c);
        }
        else {
            FjumpGet (node);
        }
    }
    for (int i = 1; i <= n; i ++) {
        sort (all (zip1[i]));
        zip1[i].erase (unique (all (zip1[i])), zip1[i].end ());
        sort (all (zip2[i]));
        zip2[i].erase (unique (all (zip2[i])), zip2[i].end ());
        T1[i].init (sz (zip1[i]));
        T2[i].init (sz (zip2[i]));
    }
    for (int i = 0; i < sz (qry); i ++) {
        auto [type, time, node, id] = qry[i];
        if (type == 0) {
            jumpUpd (node, a[id].s, a[id].c);
        }
        else {
            res[id] = jumpGet (node);
        }
    }
    for (int i = 1; i <= q; i ++) {
        cout << res[i] << '\n';
    }
    return;
}

