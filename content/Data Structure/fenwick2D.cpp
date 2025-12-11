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

struct Fenwick2D {
    int n;
    vector <int> pos[maxN], bit[maxN];
    
    void fAdd (int u, int v, int x) {
        u ++;
        v ++;
        for (; u <= n; u += u & (-u)) {
            pos[u].push_back (v);
        }
    }
    
    void fQry (int u, int v) {
        u ++;
        v ++;
        for (; u; u -= u & (-u)) {
            pos[u].push_back (v);
        }
    }
    
    void compress () {
        for (int i = 1; i <= n; i ++) {
            pos[i].push_back (0);
            sort (all (pos[i]));
            pos[i].erase (unique (all (pos[i])), pos[i].end ());
            bit[i].assign (sz (pos[i]) + 1, 0);
        }
    }
    
    void add (int u, int v, int x) {
        u ++;
        v ++;
        for (int i = u; i <= n; i += i & (-i)) {
            int st = lower_bound (all (pos[i]), v) - pos[i].begin () + 1;
            for (int j = st; j < sz (bit[i]); j += j & (-j)) {
               maximize (bit[i][j], x);
            }
        }
    }
    
    int qry (int u, int v) {
        u ++;
        v ++;
        int res = 0;
        for (int i = u; i; i -= i & (-i)) {
            int st = upper_bound (all (pos[i]), v) - pos[i].begin ();
            for (int j = st; j > 0; j -= j & (-j)) {
                maximize (res, bit[i][j]);
            }
        }
        return res;
    }
} T;

struct Val {
    int x, y, id;
};

Val a[maxN], b[maxN];
int dp[maxN];

inline void Solve () {
    cin >> n;
    vector <int> zipX, zipY;
    for (int i = 1; i <= n; i ++) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y, i};
        b[i] = a[i];
        zipX.push_back (x);
        zipX.push_back (x - 1);
        zipY.push_back (y);
        zipY.push_back (y - 1);
    }
    sort (all (zipX));
    zipX.erase (unique (all (zipX)), zipX.end ());
    sort (all (zipY));
    zipY.erase (unique (all (zipY)), zipY.end ());
    for (int i = 1; i <= n; i ++) {
        a[i].x = lower_bound (all (zipX), a[i].x) - zipX.begin () + 1;
        a[i].y = lower_bound (all (zipY), a[i].y) - zipY.begin () + 1;
    }
    T.n = sz(zipX) + 2;
    T.fAdd (0, 0, 0);
    for (int i = 1; i <= n; i ++) {
        T.fAdd (a[i].x, a[i].y, 0);
        T.fQry (a[i].x, a[i].y);
    }
    T.compress ();
    T.add (0, 0, 0);
    dp[0] = 0;
    for (int i = 1; i <= n; i ++) {
        int x = lower_bound (all (zipX), b[i].x - 1) - zipX.begin () + 1;
        int y = lower_bound (all (zipY), b[i].y - 1) - zipY.begin () + 1;
        dp[i] = T.qry (x, y) + 1;
        T.add (a[i].x, a[i].y, dp[i]);
        //cout << dp[i] << ' ';
    }
    cout << *max_element (dp + 1, dp + n + 1);
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
