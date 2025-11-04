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

int a[maxN];

void Solve () {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    deque <int> dq;
    for (int i = 1; i <= n; i ++) {
        while (!dq.empty () && a[dq.back ()] >= a[i]) {
            dq.pop_back ();
        }
        dq.push_back (i);
        while (!dq.empty () && dq.front () < i - k + 1) {
            dq.pop_front ();
        }
        if (i >= k) {
            cout << a[dq.front ()] << ' ';
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