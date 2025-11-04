#include <bits/stdc++.h>

#define task   "BriantheCrab"

#define int     long long
#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())

using namespace std;

template <class T> void mini (T &t, T f) {if (t > f) t = f;}
template <class T> void maxi (T &t, T f) {if (t < f) t = f;}

const int maxN = 2e5 + 5;
const int inf = 1e9 + 7;
const int mod = 1e9 + 7;

struct edge {
    int u, v, w;
};

bool cmp (edge A, edge B) {
    return A.w < B.w;
} 

int n;
int par[maxN], sz[maxN];
vector <edge> all;

void init () {
    for (int i = 1; i <= n; i ++) {
        par[i] = i;
        sz[i] = 1;
    }
}

int getRoot (int u) {
    if (par[u] == u) {
        return u;
    }
    return (par[u] = getRoot (par[u]));
}

void merge (int u, int v) {
    u = getRoot (u);
    v = getRoot (v);
    if (u == v) {
        return;
    }
    if (sz[u] < sz[v]) {
        swap (u, v);
    }
    par[v] = u;
    sz[u] += sz[v];
    return; 
}

void Solve () {
    int m;
    cin >> n >> m;
    init ();
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        all.push_back ({u, v, w});
    }
    sort (all.begin (), all.end (), cmp);
    int res = 0;
    for (auto [u, v, w] : all) {
        if (getRoot (u) == getRoot (v)) {
            continue;
        }
        res += w;
        merge (u, v);
    }
    cout << res;
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
// Belligerent :)
