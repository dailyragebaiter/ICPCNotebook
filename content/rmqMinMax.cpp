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

const int maxN = 2e5 + 5;
const int inf = 1e18 + 7;
const int mod = 1e9 + 7;

// khong tu code thi khong kha len duoc dau

int a[maxN];

int mx[N][LOG], mi[N][LOG], lg2[N];

void build () {
    for (int i = 1; i <= n; i ++) {
        mi[i][0] = mx[i][0] = a[i];
        lg2[i] = log2 (i);
    }
    for (int k = 1; k < LOG; k ++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i ++) {
            mi[i][k] = min (mi[i][k - 1], mi[i + (1 << k - 1)][k - 1]);
            mx[i][k] = max (mx[i][k - 1], mx[i + (1 << k - 1)][k - 1]);
        }
    }
}

int getmin (int l, int r) {
    int k = lg2[r - l +1];
    return min (mi[l][k], mi[r - (1 << k) + 1][k]);
}

int getmax (int l, int r) {
    int k = lg2[r - l + 1];
    return max (mx[l][k], mx[r - (1 << k) + 1][k]);
}

void solve () {
    
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
// thfv