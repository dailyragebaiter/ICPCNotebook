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

const int maxN = 1005;
const int inf = 1e18 + 7;
const int mod = 1e9 + 7;

int a[maxN][maxN];
int diff[maxN][maxN];

void solve () {
    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 0; i < q; ++ i) {
        int x1, y1, x2, y2, k;
        cin >> x1 >> y1 >> x2 >> y2 >> k;
        diff[x1][y1] += k;
        diff[x1][y2 + 1] -= k;
        diff[x2 + 1][y1] -= k;
        diff[x2 + 1][y2 + 1] += k;
    }

    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            a[i][j] = diff[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
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