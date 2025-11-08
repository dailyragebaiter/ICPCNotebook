#include <bits/stdc++.h>

#define task   "BriantheCrab"

#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())

using namespace std;

template <class T> void mini (T &t, T f) {if (t > f) t = f;}
template <class T> void maxi (T &t, T f) {if (t < f) t = f;}

const int maxN = 1e5 + 5;
const long long inf = 1e18 + 7;
const int mod = 1e9 + 7;

int n, k;
int a[maxN],trace[maxN][205];
long long pfs[maxN], dp[maxN][5];

void dnc (int x, int l, int r, int optL, int optR) {
    if (l > r) {
        return;
    }
    int m = (l + r) >> 1;
    long long best = -inf;
    int opt = -1;
    for (int i = optL; i <= min (m, optR); i ++) {
        if (best < dp[i - 1][(x & 1) ^ 1] + (pfs[m] - pfs[i - 1]) *  (pfs[n] - pfs[m])) {
            best = dp[i - 1][(x & 1) ^ 1] + (pfs[m] - pfs[i - 1]) *  (pfs[n] - pfs[m]);
            opt = i;
        }
    }
    dp[m][(x & 1)] = best;
    //cout << m << ' ' << x << ' ' << dp[m][x & 1] << ' ' << opt << '\n';
    trace[m][x] = opt - 1;
    dnc (x, l, m - 1, optL, opt);
    dnc (x, m + 1, r, opt, optR); 
}

void solve () {
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        pfs[i] = pfs[i - 1] + a[i];
    }
    memset (trace, -1, szf (trace));
    for (int i = 1; i <= n; i ++) {
        dp[i][1] = pfs[i] * (pfs[n] - pfs[i]);
    }
    for (int i = 1; i <= k + 1; i ++) {
        dnc (i, i, n, i, n);
    }
    cout << max (0LL, dp[n][(k + 1) & 1]) << '\n';
    int curM = n, curX = k + 1;
    vector <int> all;
    all.push_back (curM - 1);
    while (trace[curM][curX] != -1) {
        all.push_back (trace[curM][curX]);
        curM = trace[curM][curX];
        curX --;       
    }
    reverse (all.begin (), all.end ());
    for (int i = 1; i <= k; i ++) {
        cout << all[i] << ' ';
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
        solve ();
    } 
    return 0;
}
// thfdgb