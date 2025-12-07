#include <bits/stdc++.h>

#define task   "taskname"

#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())
#define all(v) (v).begin(), (v).end()

using namespace std;

typedef long long ll;
typedef long double ld;

template <class T> void minimize (T &t, T f) {if (t > f) t = f;}
template <class T> void maximize (T &t, T f) {if (t < f) t = f;}

const int maxN = 4e4 + 5;
const ld Eps = 1e-12;
const int inf = 1e9 + 7;
const int Log = 20;
const int mod = 1e9 + 7;

// mt19937_64 rd (chrono :: steady_clock :: now ().time_since_epoch ().count ());
// int Rand (int l, int r) {return uniform_int_distribution <int> (l, r) (rd);}

int n, m, s, t;
int maxFlow;

struct Edge {
    int v, rev, cap;
};

vector <Edge> adj[maxN];
vector <int> curId, d;

int p1[maxN], p2[maxN], a[maxN], b[maxN]; 
vector <int> g1[maxN], g2[maxN];
int sz1[maxN], sz2[maxN];

void dfs1 (int u, int p) {
    sz1[u] = 1;
    for (auto v : g1[u]) {
        if (v == p) {
            continue;
        }
        dfs1 (v, u);
        sz1[u] += sz1[v];
    }
}

void dfs2 (int u, int p) {
    sz2[u] = 1;
    for (auto v : g2[u]) {
        if (v == p) {
            continue;
        }
        dfs2 (v, u);
        sz2[u] += sz2[v];
    }
}

void bfs () {
    fill (all (d), inf);
    d[s] = 0;
    queue <int> q;
    q.push (s);
    while (!q.empty ()) {
        int u = q.front ();
        q.pop ();
        for (auto edge : adj[u]) {
            int v = edge.v;
            if (d[v] != inf) {
                continue;
            }
            if (edge.cap == 0) {
                continue;
            }
            d[v] = d[u] + 1;
            q.push (v);
        }
    }
}

int incFlow (int u, int delta) {
    if (delta == 0) {
        return 0;
    }
    if (u == t) {
        return delta;
    }
    for (; curId[u] < sz (adj[u]); curId[u] ++) {
        auto &[v, rev, cap] = adj[u][curId[u]];
        if (d[v] != d[u] + 1) {
            continue;
        }
        if (cap == 0) {
            continue;
        }
        int ndelta = incFlow (v, min (cap, delta));
        if (ndelta == 0) {
            continue;
        }
        cap -= ndelta;
        adj[v][rev].cap += ndelta;
        return ndelta;
    }
    return 0;
}

inline void addEdge (int x, int y, int w) {
    Edge f = {y, sz (adj[y]), w};
    Edge b = {x, sz (adj[x]), 0}; 
    adj[x].push_back (f);
    adj[y].push_back (b);
}

inline void Solve () {
    cin >> n;
    s = 1, t = 2 + n + n;
    d.assign (t + 1, 0);
    curId.assign (t + 1, 0);
    int rt1 = 0, rt2 = 0;
    for (int i = 1; i <= n; i ++) {
        cin >> p1[i];
        if (p1[i] == 0) {
            rt1 = i;
        }
        else {
            g1[p1[i]].push_back (i);
            g1[i].push_back (p1[i]);
        }
    }
    for (int i = 1; i <= n; i ++) {
        cin >> p2[i];
        if (p2[i] == 0) {
            rt2 = i;
        } 
        else {
            g2[p2[i]].push_back (i);
            g2[i].push_back (p2[i]);
        }
    }
    dfs1 (rt1, rt1);
    dfs2 (rt2, rt2);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i ++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i ++) {
        if (p1[i] == 0) {
            addEdge (s, i + 1, n - a[i]);
        }
        else {
            addEdge (p1[i] + 1, i + 1, sz1[i] - a[i]);
        }
    }

    for (int i = 1; i <= n; i ++) {
        addEdge (i + 1, i + n + 1, 1);
    }

    for (int i = 1; i <= n; i ++) {
        if (p2[i] == 0) {
            addEdge (i + n + 1, t, n - b[i]);
        }
        else {
            addEdge (i + n + 1, p2[i] + n + 1, sz2[i] - b[i]);
        }
    }
    maxFlow = 0;
    while (true)
    {
        bfs();
        if (d[t] == inf) {
            break;
        }
        for (int i = 1; i <= t; i ++) {
            curId[i] = 0;
        }
        while (int delta = incFlow (s, inf)) {
            maxFlow += delta;
        }
    }
    cout << n - maxFlow << '\n';
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
// Stress test : 
// Check constant :
// Check taskname :
// Check debug :
// Check subtask :
