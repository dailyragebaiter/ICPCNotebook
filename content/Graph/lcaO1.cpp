int a[maxN];

vector <int> adj[maxN];
vector <int> euler_tour;
vector <int> dep;
vector <int> first_occ;
vector <vector <int>> spt;
vector <int> log_tab;

void dfs (int u, int p, int d) {
    euler_tour.push_back (u);
    dep.push_back (d);
    if (first_occ[u] == -1) {
        first_occ[u] = sz(euler_tour) - 1;
    }
    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        dfs (v, u, d + 1);
        euler_tour.push_back (u);
        dep.push_back (d);
    }
}

int query_rmq (int l, int r) {
    int k = log_tab[r - l + 1];
    int u = spt[l][k];
    int v = spt[r - (1 << k) + 1][k];
    if (dep[u] < dep[v]) {
        return u;
    }
    return v;
}

int lca (int u, int v) {
    int idx_u = first_occ[u];
    int idx_v = first_occ[v];
    if (idx_u > idx_v) {
        swap (idx_u, idx_v);
    }
    int res_idx = query_rmq (idx_u, idx_v);
    return euler_tour[res_idx];
}

void solve () {
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n - 1; ++ i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
        adj[v].push_back (u);
    }

    first_occ.assign (n + 1, -1);
    dfs (1, 0, 0); // Start DFS from node 1 with depth 0

    int len_euler = sz(euler_tour);
    log_tab.assign (len_euler + 1, 0);
    for (int i = 2; i <= len_euler; ++ i) {
        log_tab[i] = log_tab[i / 2] + 1;
    }

    int max_log = log_tab[len_euler];
    spt.assign (len_euler, vector <int> (max_log + 1));

    for (int i = 0; i < len_euler; ++ i) {
        spt[i][0] = i;
    }

    for (int j = 1; j <= max_log; ++ j) {
        for (int i = 0; i + (1 << j) <= len_euler; ++ i) {
            int u_idx = spt[i][j - 1];
            int v_idx = spt[i + (1 << (j - 1))][j - 1];
            if (dep[u_idx] < dep[v_idx]) {
                spt[i][j] = u_idx;
            } else {
                spt[i][j] = v_idx;
            }
        }
    }

    while (q --) {
        int u, v;
        cin >> u >> v;
        cout << lca (u, v) << "\n";
    }

    return;
}
