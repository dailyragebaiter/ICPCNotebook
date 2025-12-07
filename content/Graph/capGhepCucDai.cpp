int a[maxN];
vector <int> adj[maxN];
int V1, V2, E;
int match_v[maxN];
bool visited[maxN];

bool dfs_augment (int u) {
    for (int v : adj[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (match_v[v] == 0 || dfs_augment (match_v[v])) {
                match_v[v] = u;
                return true;
            }
        }
    }
    return false;
}

void solve () {
    cin >> V1 >> V2 >> E;
    for (int i = 0; i < E; ++ i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
    }
    
    int matching_size = 0;
    for (int u = 1; u <= V1; ++ u) {
        for (int i = 1; i <= V2; ++ i) {
            visited[i] = false;
        }
        if (dfs_augment (u)) {
            matching_size ++;
        }
    }
    
    cout << matching_size << '\n';
    
    return;
}
