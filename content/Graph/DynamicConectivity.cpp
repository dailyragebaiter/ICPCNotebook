#include <bits/stdc++.h>

#define task     "BriantheCrab"

#define int    long long
#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())
#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

template <class T> void minimize (T &t, T f) {if (t > f) t = f;}
template <class T> void maximize (T &t, T f) {if (t < f) t = f;}

const int maxN = 5e5 + 5;
const int inf = 1e18 + 7;
const int mod = 1e9 + 7;

int n;
map <pii, int> mp;
int res = 0;
int sad[maxN * 4];
struct Edge {
    int u, v;
};

vector <Edge> Ed[maxN];

struct DsuRollBack {
    vector <int> par, sz;
    stack <pii> rollback;
    vector <vector <pii>> ed;
    int sum = 0;
    
    void init (int _n, int _q) {
        par.resize (_n + 2);
        sz.resize (_n + 2);
        ed.clear ();
        ed.resize (_q * 4 + 2);
        sum = 0;
        for (int i = 1; i <= _n; i ++) {
            sz[i] = 1;
            par[i] = i;
        }
        while (!rollback.empty ()) rollback.pop ();
    }
    
    inline int getRoot (int u) {
        while (par[u] != u) {
            u = par[u];
        }
        return u;
    }
    
    void upd (int id, int l, int r, int L, int R, pii curEd) {
        if (l > R || r < L) {
            return;
        } 
        if (l >= L && r <= R) {
            ed[id].push_back (curEd);
            return;
        }
        int mid = (l + r) >> 1;
        upd (id * 2, l, mid, L, R, curEd);
        upd (id * 2 + 1, mid + 1, r, L, R, curEd);
    }
    
    void get (int id, int l, int r) {
        int cnt = 0;
        for (auto [u, v] : ed[id]) {
            int rootU = getRoot (u);
            int rootV = getRoot (v);
            if (rootU == rootV) {
                continue;
            }
            if (sz[rootU] < sz[rootV]) {
                swap (rootU, rootV);
            }
            rollback.push ({rootV, sz[rootV]});
            rollback.push ({rootU, sz[rootU]});
            cnt += 2;
            par[rootV] = rootU;
            sz[rootU] += sz[rootV];
        }
 
        if (l == r) {
            //cout << sad[l] << ' ' << l << '\n';
            //cout << sad[l] << '\n';
            for (auto [u, v] : Ed[sad[l]]) {
                //cout << u << ' ' << v << '\n';
                u = getRoot (u);
                v = getRoot (v);
                //cout << u <<  ' ' << v << '\n';
                //cout << sz[u] << ' ' << sz[v] << '\n';
                res += sz[u] * sz[v];
            }
        }
        else {
            int mid = (l + r) >> 1;
            get (id * 2, l, mid);
            get (id * 2 + 1, mid + 1, r);
        }
        while (cnt > 0) {    
            auto [u, s1] = rollback.top (); rollback.pop ();
            auto [v, s2] = rollback.top (); rollback.pop ();
            cnt -= 2;
            par[u] = u;
            par[v] = v;
            sz[u] = s1;
            sz[v] = s2;
        }
    }
} dsu;

struct query {
    int u, v, type;
};

vector <query> qry;

void solve () {
    cin >> n;
    for (int i = 1; i <= n - 1; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u > v) {
            swap (u, v);
        }
        Ed[w].push_back ({u, v});
    }
    for (int i = 1; i <= n; i ++) {
        for (auto [u, v] : Ed[i]) {
            //mp[{u, v}] = i;
            qry.push_back ({u, v, 1});
        }
    }
    for (int i = 1; i <= n; i ++) {
        if (sz (Ed[i]) == 0) {
            continue;
        }
        for (auto [u, v] : Ed[i]) {
            qry.push_back ({u, v, 2});
        }
        qry.push_back ({i, i, 3});
        for (auto [u, v] : Ed[i]) {
            qry.push_back ({u, v, 1});
        }
    }
    int q = sz (qry);
    dsu.init (n,  q);
    for (int i = 1; i <= sz (qry); i ++) {
        auto [u, v, t] = qry[i - 1];
        if (t == 1) {
            mp[{u, v}] = i;
        }
        else if (t == 2) {
            auto it = mp.find ({u, v});
            if (it != mp.end ()) {
                dsu.upd (1, 1, q, it -> se, i - 1, {u, v});
                mp.erase (it);
            }
        }
        else {
            //cout << i << ' ' << sad[i] << '\n';
            sad[i] = u; 
        }
    }
    for (auto it : mp) {
        int u = it.first.first;
        int v = it.first.second;
        int L = it.second;
        dsu.upd(1, 1, q, L, q, {u, v});
    }
    mp.clear ();
    dsu.get (1, 1, q);
    cout << res;
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
// thfv
