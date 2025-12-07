int a[maxN];

int V, E, s;
vector <pii> adj[maxN];
int dist[maxN];
bool inQueue[maxN];
int cnt[maxN];

void solve () {
    cin >> V >> E >> s;
    for (int i = 0; i < E; ++ i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back ({v, w});
    }
    
    for (int i = 1; i <= V; ++ i) {
        dist[i] = inf;
        inQueue[i] = false;
        cnt[i] = 0;
    }
    
    queue <int> q;
    q.push (s);
    dist[s] = 0;
    inQueue[s] = true;
    cnt[s] = 1;
    
    while (!q.empty ()) {
        int u = q.front ();
        q.pop ();
        inQueue[u] = false;
        
        for (auto &edge : adj[u]) {
            int v = edge.fi;
            int w = edge.se;
            
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inQueue[v]) {
                    q.push (v);
                    inQueue[v] = true;
                    cnt[v] ++;
                    
                    if (cnt[v] >= V) {
                        cout << "Graph contains a negative cycle." << '\n';
                        return;
                    }
                }
            }
        }
    }
    
    for (int i = 1; i <= V; ++ i) {
        if (dist[i] == inf) {
            cout << "INF" << '\n';
        } else {
            cout << dist[i] << '\n';
        }
    }

    return;
}
