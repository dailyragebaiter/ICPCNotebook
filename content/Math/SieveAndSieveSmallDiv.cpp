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

int a[maxN];

namespace Sieve {
    vector <bool> check;
    vector <int> spf;
    
    void calPrime (int lim) {
        check.resize (lim + 1, true);
        check[0] = check[1] = 0;
        for (int i = 2; i * i <= lim; i ++) {
            if (check[i]) {
                for (int j = i * i; j <= lim; j += i) {
                    check[j] = 0;
                }
            }
        }
        return;
    }
    
    void calDiv (int lim) {
        spf.resize (lim + 1);
        for (int i = 1; i <= lim; i ++) {
            spf[i] = i;
        }
        for (int i = 1; i * i <= lim; i ++) {
            if (spf[i] == i) {
                for (int j = i * i; j <= lim; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
        return;
    }
    
    void calFactor (int x, vector <int> &f) {
        while (x > 1) {
            f.push_back (spf[x]);
            x /= spf[x];
        }
        return;
    }
}

void solve () {
    int n;
    cin >> n;
    Sieve :: calPrime (n);
    for (int i = 1; i <= n; i ++) {
        if (Sieve :: check[i]) {
            cout << i << ' ';
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
        solve ();
    } 
    return 0;
}
// thfv