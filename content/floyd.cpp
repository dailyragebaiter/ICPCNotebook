#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 4e3 + 5;
const int inf = 1e18 + 7;

struct pii {
    int fi, se;
};

struct cmp {
    bool operator () (pii A, pii B) {
        return A.fi > B.fi;
    }
};

int d[N][N], mem[N][N], L[N];
int n, m, k;
vector<pii> adj[N], adj1[N];
vector<pii> original_adj[N], original_adj1[N];

void floyd () {
    for (int k = 1; k <= n; k ++) {
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= n; j ++) {
                if (d[i][k] != inf && d[k][j] != inf && d[i][j] >= d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

void floyd_reup () {
    for (int k = n + 1; k <= n + 1; k ++) {
        for (int i = 1; i <= n + 1; i ++) {
            for (int j = 1; j <= n + 1; j ++) {
                d[i][j] = min (d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

void dijkstra (int s) {
    priority_queue<pii, vector<pii>, cmp> pq;
    d[s][s] = 0;
    pq.push({d[s][s], s});
    while (!pq.empty ()) {
        int c = pq.top ().fi;
        int u = pq.top ().se;
        //cout << u << " " << c << " " << d[s][u]  << " " << '\n';
        pq.pop();
        if (c > d[s][u]) {
            continue;
        }
        for (auto v : adj[u]) {
            //cout << d[s][v.fi] << '\n';
            if (d[s][v.fi] >= d[s][u] + v.se && d[s][v.fi] != 0) {
                d[s][v.fi] = d[s][u] + v.se;
                d[v.fi][s] = d[s][v.fi];
                pq.push({d[s][v.fi], v.fi});
            }
        }
    }
}

int cal() {
    int ans = 0;
    for (int i = 1; i <= n ; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (i == j) {
                continue;
            }
            int tmp = d[i][j];
            if (tmp == inf) {
                tmp = 0;
            }
            ans += tmp;
        }
    }
    return ans;
}

void resol() {
    dijkstra(n + 1);
    floyd_reup ();
}

void reset_graph () {
    for (int i = 1; i <= n + 3; i++) {
        adj[i] = original_adj[i];
        adj1[i] = original_adj1[i];
    }
     for (int i = 1; i <= n + 3; i ++) {
        for (int j = 1; j <= n + 3; j ++) {
           d[i][j] = mem[i][j];
        }
    }
}

signed main () {
    ios_base :: sync_with_stdio (0);
    cin.tie (0);
    cout.tie (0);
    cin >> n >> m;
    for (int i = 1; i <= n + 3; i ++) {
        for (int j = 1; j <= n + 3; j ++) {
            d[i][j] = inf;
            mem[i][j] = inf;
        }
    }
    vector <pii> edges;
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        d[u][v] = min (d[u][v], w);
        d[v][u] = d[u][v];
        adj[u].push_back ({v, w});
        adj[v].push_back ({u, w});
        edges.push_back ({u, v});
    }
    for (int i = 1; i <= n; i ++) {
        original_adj[i] = adj[i];
    }
    floyd ();
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            mem[i][j] = d[i][j];
        }
    }
    int res = inf;
    for (int i = 1; i <= n + 1; i ++) {
        for (int j = 1; j <= n + 1; j ++) {
            if (i == j) {
                continue;
            }
            int u = i;
            int v = j;
            adj[n + 1].push_back ({v, 0});
            adj[v].push_back ({n + 1, 0});
            adj[u].push_back ({n + 1, 0});
            adj[n + 1].push_back ({u, 0});
            resol ();
            //cout << cal () << '\n';
            res = min (res, cal ());
            reset_graph ();
        }
    }
    cout << res;
    return 0;
}