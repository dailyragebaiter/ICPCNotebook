#include <bits/stdc++.h>

#define task   "htgdtctn"

#define int    long long
#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())
#define all(v) (v).begin(), (v).end()

using namespace std;

template <class T> void minimize (T &t, T f) {if (t > f) t = f;}
template <class T> void maximize (T &t, T f) {if (t < f) t = f;}

const int maxN = 2e5 + 5;
const int inf = 1e18 + 7;
const int mod = 1e9 + 7;

// mt19937_64 rd (chrono :: steady_clock :: now ().time_since_epoch ().count ());
// int Rand (int l, int r) {return uniform_int_distribution <int> (l, r) (rd);}

int n;
int c[maxN];
int sz[maxN], big[maxN];
int st[maxN], en[maxN];
int ver[maxN], cnt[maxN];
vector <int> adj[maxN];
int timer = 0;
int res[maxN];

void dfsPre (int u, int p) {
    sz[u] = 1;
    big[u] = -1;
    st[u] = ++timer;
    ver[timer] = u;
    for (auto v : adj[u]) {
        if (v == p) {
            continue;
        }
        dfsPre (v, u);
        sz[u] += sz[v];
        if (big[u] == -1 || sz[big[u]] < sz[v]) {
            big[u] = v;
        }
    }
    en[u] = timer;
}

int mx = 0, sum = 0;

void dfs (int u, int p, bool keep) {
    //cout << u << ' ' << p << '\n';
    for (auto v : adj[u]) {
        if (v == p || v == big[u]) {
            continue;
        }
        dfs (v, u, 0);
    }
    if (big[u] != -1) {
        dfs (big[u], u, 1);
    }
    for (auto v : adj[u]) {
        if (v != p && v != big[u]) {
            for (int k = st[v]; k <= en[v]; k ++) {
                cnt[c[ver[k]]] ++;
                if (mx == cnt[c[ver[k]]]) {
                    sum += c[ver[k]];
                }
                else if (mx < cnt[c[ver[k]]]) {
                    mx = cnt[c[ver[k]]];
                    sum = c[ver[k]];
                }
            }
        }
    }
    cnt[c[u]] ++;
    if (mx == cnt[c[u]]) {
        mx = cnt[c[u]];
        //cout << c[u] << ' ' << u << '\n';
        sum += c[u];
    }
    else if (mx < cnt[c[u]]) {
        mx = cnt[c[u]];
        sum = c[u];
    }
    res[u] = sum;
    if (keep == 0) {
        for (int k = st[u]; k <= en[u]; k ++) {
            cnt[c[ver[k]]] --;
        }
        mx = 0, sum = 0;
    }
}

inline void Solve () {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> c[i];
    }
    for (int i = 1; i <= n - 1; i ++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back (y);
        adj[y].push_back (x);
    }
    dfsPre (1, 1);
    dfs (1, 1, 1);
    for (int i = 1; i <= n; i ++) {
        cout << res[i] << ' ';
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
// wake me up when September ends
