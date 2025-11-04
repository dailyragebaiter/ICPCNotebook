#include <bits/stdc++.h>

#define task   "BriantheCrab"

#define int    long long
#define ll     long long
#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())

using namespace std;

template <class T> void mini (T &t, T f) {if (t > f) t = f;}
template <class T> void maxi (T &t, T f) {if (t < f) t = f;}

const int maxN = 3e4 + 5;
const ll inf = 1e18 + 7;
const int mod = 1e9 + 7;

int n, m;
int a[maxN];
ll Ls[maxN], Lt[maxN];
ll Cs[maxN], Ct[maxN];
vector <pii> adj[maxN];

struct edge {
    int node;
    ll dis;
};

struct cmp {
    bool operator () (edge A, edge B) {
        return A.dis > B.dis;
    }
};

void dijkstraS () {
    Ls[1] = 0;
    Cs[1] = 1;
    priority_queue <edge, vector <edge>, cmp> pq;
    pq.push ({1, 0});
    while (!pq.empty ()) {
        auto [u, c] = pq.top ();
        pq.pop ();
        if (c > Ls[u]) {
            continue;
        }
        for (auto [v, dis] : adj[u]) {
            if (Ls[v] > Ls[u] + dis) {
                Ls[v] = Ls[u] + dis;
                pq.push ({v, Ls[v]});
                Cs[v] = Cs[u];
            }
            else if (Ls[v] == Ls[u] + dis) {
                Cs[v] += Cs[u];
            }
        }
    }
}

void dijkstraT () {
    Lt[n] = 0;
    Ct[n] = 1;
    priority_queue <edge, vector <edge>, cmp> pq;
    pq.push ({n, 0});
    while (!pq.empty ()) {
        auto [u, c] = pq.top ();
        pq.pop ();
        if (c > Lt[u]) {
            continue;
        }
        for (auto [v, dis] : adj[u]) {
            if (Lt[v] > Lt[u] + dis) {
                Lt[v] = Lt[u] + dis;
                pq.push ({v, Lt[v]});
                Ct[v] = Ct[u];
            }
            else if (Lt[v] == Lt[u] + dis) {
                Ct[v] += Ct[u];
            }
        }
    }
}

void Solve () {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back ({v, w});
        adj[v].push_back ({u, w});
    }
    for (int i = 1; i <= n; i ++) {
        Ls[i] = Lt[i] = inf;
    }
    dijkstraS ();
    dijkstraT ();
    int best = Ls[n];
    vector <int> res;
    //cout << Cs[2] << ' ' << Ct[2] << ' ' << Ct[1] << '\n';
    for (int i = 2; i <= n - 1; i ++) {
        if (!(Ls[i] + Lt[i] == best && Cs[i] * Ct[i] == Cs[n])) {
            res.push_back (i);
        }
    }
    cout << sz (res) << '\n';
    for (auto cur : res) {
        cout << cur << '\n';
    }
    return;
}

signed main () {
    ios_base :: sync_with_stdio (false);
    cin.tie (0);
    cout.tie (0);
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
