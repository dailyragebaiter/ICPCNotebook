#include <bits/stdc++.h>

#define int long long

using namespace std;

mt19937_64 rd (chrono :: steady_clock :: now ().time_since_epoch ().count ());
int Rand (int l, int r) {return uniform_int_distribution <int> (l, r) (rd);}

void Solve () {
    cout << Rand (1, 50);
}

signed main () {
    ios_base :: sync_with_stdio (0);
    cin.tie (0);
    freopen ("task.inp", "w", stdout);
    int t = 1;
    // cin >> t;
    while (t --) {
        Solve ();
    }
    return 0;
}
