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

const int maxN = 1e3 + 5;
const int inf = 1e18 + 7;
const int mod = 1e9 + 7;

int n, m, s, t;
int maxFlow;
int c[maxN][maxN], f[maxN][maxN], trace[maxN];
vector <int> adj[maxN];

void bfs () {
    fill (trace, trace + n + 4, 0);
    trace[s] = -1;
    queue <int> q;
    q.push (s);
    while (!q.empty ()) {
        int u = q.front ();
        q.pop ();
        for (auto v : adj[u]) {
            if (trace[v]) {
                continue;
            }
            if (f[u][v] - c[u][v] == 0) {
                continue;
            }
            trace[v] = u;
            q.push (v);
        }
    }
}

void incFlow () {
    int delta = inf;
    int v = t;
    while (v != s) {
        int u = trace[v];
        mini (delta, c[u][v] - f[u][v]);
        v = u;
    }
    maxFlow += delta;
    v = t;
    while (v != s) {
        int u = trace[v];
        f[u][v] += delta;
        f[v][u] -= delta;
        v = u;
    }
}

void solve () {
    cin >> n;
    s = n + 1, t = n + 2;
    int add = 0;
    for (int i = 1; i <= n; i ++) {
        int x;
        cin >> x;
        if (x > 0) {
            adj[s].push_back (i);
            adj[i].push_back (s);
            c[s][i] = x;
            add += x;
            //cout << s << ' ' << i << ' ' << x << '\n';
        }
        else {
            adj[i].push_back (t);
            adj[t].push_back (i);
            c[i][t] = -x;
            //cout << i << ' ' << t << ' ' << -x << '\n';
        }
    }
    cin >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        c[u][v] = add + 1;
        adj[u].push_back (v);
        adj[v].push_back (u);
        //cout << u << ' ' << v << ' ' << inf << '\n';
    }
    maxFlow = 0;
    do {
        bfs ();
        //cout << trace[t] << '\n';
        if (trace[t]) {
            incFlow ();
        }
    } while (trace[t]);
    cout << add - maxFlow;
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
        solve ();
    } 
    return 0;
}
// thfdgb
