int n, m;
bool visited[maxN]; 
vector <pii> adj[maxN];
vector <pii> ed;
int deg[maxN];
vector <vector <int>> res;
map <pii, int> mp;

list <pii> euler (int u) {
    list <pii> ans;
    while (!adj[u].empty()) {
        auto [v, id] = adj[u].back ();
        adj[u].pop_back ();
        if (visited[id]) {
            continue;
        }
        visited[id] = true;
        auto t = euler (v);
        ans.splice (ans.end (), t);
        ans.push_back ({v, id > m});
    }
    return ans;
}

inline void Solve () {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back ({v, i});
        adj[v].push_back ({u, i});
        mp[{u, v}] ++;
        deg[u] ++;
        deg[v] ++;
    }
    vector <int> odd;
    for (int i = 1; i <= n; i ++) {
        if (deg[i] & 1) {
            odd.push_back (i);
        }
    }
    int cnt = m;
    for (int i = 0; i + 1 < sz (odd); i += 2) {
        int u = odd[i];
        int v = odd[i + 1];
        cnt ++;
        adj[u].push_back ({v, cnt});
        adj[v].push_back ({u, cnt});
        //cout << u << ' ' << v << '\n';
    }
    for (int i = 0; i + 1 < sz (odd); i += 2) {
        auto cur = euler (odd[i]);
        if (sz (cur) <= 1) {
            continue;
        }
        vector <int> ok;
        for (auto [it, t] : cur) {
            ok.push_back (it);
            if (t == 1) {
                res.push_back (ok);
                ok.clear ();
            }
        }
        if (sz (ok) != 0) {
            res.push_back (ok);
        }
    }
    cout << sz (res) << '\n';
    for (auto cur : res) {
        vector <int> v;
        for (auto it : cur) {
            v.push_back (it);
        }
        cout << sz (v) << ' ';
        for (int i = 0; i < sz (v); i ++) {
            cout << v[i] << ' ';
        }
        cout << '\n';
    }
    return;
}