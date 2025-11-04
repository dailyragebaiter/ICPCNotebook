#include <bits/stdc++.h>

#define task   "BriantheCrab"

#define ll     long long
#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())

using namespace std;

template <class T> void mini (T &t, T f) {if (t > f) t = f;}
template <class T> void maxi (T &t, T f) {if (t < f) t = f;}

const int maxN = 1e5 + 5;
const int inf = 1e9 + 7;
const int mod = 1e9 + 7;

int n;
int par[maxN], sz[maxN];
map <int, int> mp[maxN];

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
    for (auto cur : mp[v]) {
        mp[u][cur.fi] += cur.se;
    }
    mp[v].clear ();
    return;
}

void Solve () {
    int q;
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) {
        int x;
        cin >> x;
        mp[i][x] ++;
        par[i] = i;
        sz[i] = 1;
    }
    while (q --) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1) {
            merge (u, v);
        }
        else {
            cout << mp[getRoot (u)][v] << '\n';
        }
    }
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
