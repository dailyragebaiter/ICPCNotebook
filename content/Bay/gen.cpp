#include <bits/stdc++.h>

#define task     "BriantheCrab"

#define int    long long
#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())
#define all(v) (v).begin(), (v).end()

using namespace std;

mt19937_64 rd (chrono :: steady_clock :: now ().time_since_epoch ().count ());

long long Rand (long long l, long long r)
{
    return uniform_int_distribution <long long> (l, r) (rd);
}

void gen ()
{
    freopen ("bai1.inp", "w", stdout);
    int n = Rand(5, 5e3);
    cout << n << '\n';
    for (int i = 1; i <= n; i ++) {
        cout << Rand (1, 2e2) << ' ';
    }
}

signed main ()
{
    gen ();
    return 0;
}
