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

const int maxN = 2e5 + 5;
const int inf = 1e18 + 7;
const int mod = 1e9 + 7;
const int LOG = 20;

vector <int> adj[maxN], aux[maxN * 2];
int dfsTime = 0;
int tIn[maxN], tOut[maxN], h[maxN];
int up[maxN][LOG];

void dfs (int u, int p) {
    tIn[u] = ++ dfsTime;
    up[u][0] = p;
    for (int j = 1; j < LOG; j ++) {
        up[u][j] = ((up[u][j - 1] == -1) ? -1 : up[up[u][j - 1]][j - 1]);
    }
    for (auto v : adj[u]) {
        if (v != p) {
            h[v] = h[u] + 1;
            dfs (v, u);
        }
    }
    tOut[u] = dfsTime;
}

bool isAnces (int u, int v) {
    return (tIn[u] <= tIn[v] && tIn[v] <= tOut[u]);
}

int lca (int u, int v) {
    if (isAnces (u, v)) {
        return u;
    }
    if (isAnces (v, u)) {
        return v;
    }
    for (int j = LOG - 1; j >= 0; j --) {
        if (up[u][j] != -1 && !isAnces (up[u][j], v)) {
            u = up[u][j];
        }
    }
    u = up[u][0];
    return u;
}

bool cmp (int u, int v) {
    return tIn[u] < tIn[v];
}

int buildAuxiliary (vector <int> &all) {
    int sz = (int) all.size ();
    sort (all.begin (), all.end (), cmp);
    for (int i = 0; i < sz - 1; i ++) {
        int newVer = lca (all[i], all[i + 1]);
        all.push_back (newVer);
    } 
    sort (all.begin (), all.end (), cmp);
    all.erase (unique (all.begin (), all.end ()), all.end ());
    stack <int> st;
    int auxRoot = all[0];
    st.push (auxRoot);
    for (int i = 1; i < all.size (); i ++) {
        int u = all[i];
        while (!st.empty () && !isAnces (st.top (), u)) {
            st.pop ();
        }
        int last = st.top ();
        aux[last].push_back (u);
        //cout << last << ' ' << u << '\n';
        st.push (u);
    }
    return auxRoot;
}

void solve () {
    int n;
    cin >> n;
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
        adj[v].push_back (u);
    }
    dfs (1, -1);
    int q;
    cin >> q;
    while (q --) {
        int k;
        cin >> k;
        vector <int> all (k);
        for (int i = 0; i < k; i ++) {
            cin >> all[i];
        }
        int auxRoot = buildAuxiliary (all);
        bool passable = true;
        for (int u : all) {
            if (aux[u].size() > 1 + (u == auxRoot)) {
                passable = false;
                break;
            }
        }
        cout << (passable ? "YES\n" : "NO\n");
        for (int u : all) {
            aux[u].clear ();
        }
    }
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