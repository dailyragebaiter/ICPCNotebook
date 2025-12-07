int n;
int a[maxN], h[maxN];
int mx[maxN][LOG], par[maxN][LOG];
vector <int> adj[maxN];
int dp[maxN];

void dfs (int u, int p) {
    par[u][0] = p;
    mx[u][0] = a[u];
    for (int j = 1; j <= LOG - 1; j ++) {
        par[u][j] = par[par[u][j - 1]][j - 1];
        mx[u][j] = max (mx[u][j - 1], mx[par[u][j - 1]][j - 1]);
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
    int res = 0;
    for (int j = LOG - 1; j >= 0; j --) {
        if ((k >> j) & 1) {
            res = max (res, mx[u][j]);
            u = par[u][j];
        }
    }
    if (u == v) {
        return max ({res, a[u], a[v]});
    }
    for (int j = LOG - 1; j >= 0; j --) {
        if (par[u][j] != par[v][j]) {
            res = max ({res, mx[u][j], mx[v][j]});
            u = par[u][j];
            v = par[v][j];
        }
    }
    return max ({res, a[par[u][0]], a[u], a[v]});
}
 

void solve () {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n - 1; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
        adj[v].push_back (u);
    }
    int k;
    cin >> k;
    dfs (1, 0);
    for (int i = 1; i <= n; i ++) {
        dp[i] = -inf;
    }
    dp[1] = 0;
    for (int i = 1; i <= k; i ++) {
        int u, v;
        cin >> u >> v;
        if (dp[u] == -inf) {
            continue;
        }
        maxi (dp[v], dp[u] + LCA (u, v));
    }
    cout << *max_element (dp + 1, dp + n + 1);
}
