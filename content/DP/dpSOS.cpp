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

const int maxN = 2e6 + 5;
const int inf = 1e18 + 7;
const int mod = 1e9 + 7;

int a[maxN];
int f[(1 << 20) + 1];

void solve () {
    int n;
    cin >> n;
    for (int i = 0; i < (1 << n); i ++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i ++) {
        for (int mask = 0; mask < (1 << n); mask ++) {
            if ((mask >> i) & 1) {
                a[mask] += a[mask ^ (1 << i)];
            }
        }
    }
    for (int i = 0; i < (1 << n); i ++) {
        cout << a[i] << ' ';
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
// thfv
