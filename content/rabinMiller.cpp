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
const int mod = 1e9 + 7; // Not used for actual modulo in Rabin-Miller, only for general template.

// Function to calculate (a * b) % m for large numbers
// Using __int128 for intermediate product to prevent overflow
ll multiply (ll a, ll b, ll m) {
    return (__int128) a * b % m;
}

// Function to calculate (base^exp) % mod
ll power (ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = multiply (res, base, mod);
        }
        base = multiply (base, base, mod);
        exp /= 2;
    }
    return res;
}

// Rabin-Miller primality test
// 'n' is the number to be tested
// 'a' is the witness
bool check_composite (ll n, ll a, ll d, int s) {
    ll x = power (a, d, n);
    if (x == 1 || x == n - 1) {
        return false; // n is probably prime
    }
    for (int r = 1; r < s; ++ r) {
        x = multiply (x, x, n);
        if (x == n - 1) {
            return false; // n is probably prime
        }
    }
    return true; // n is composite
}

bool is_prime (ll n) {
    if (n < 2) {
        return false;
    }
    if (n == 2 || n == 3) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }

    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s ++;
    }

    // Set of witnesses for numbers up to ~3.3 * 10^14
    // For n < 2^64, a fixed set of witnesses can deterministically check primality.
    // For larger numbers or general probabilistic test, use random 'a' values.
    // Witnesses for 64-bit integers: 2, 325, 9375, 28178, 450775, 9780504, 1795265022
    // A smaller set for n < 3,317,044,064,679,887,385 (2^61.8) : 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
    // For smaller ranges, even fewer are needed.
    // The provided set [2, 3, 5, 7, 11, 13, 17] is good for n up to 341,550,071,728,321
    vector<ll> witnesses = {2, 3, 5, 7, 11, 13, 17}; 

    for (ll a : witnesses) {
        if (a >= n) { // If witness is greater than or equal to n, skip it
            continue;
        }
        if (check_composite (n, a, d, s)) {
            return false; // n is definitely composite
        }
    }
    return true; // n is probably prime
}

void solve () {
    ll n;
    cin >> n;
    if (is_prime (n)) {
        cout << n << " is prime\n";
    } else {
        cout << n << " is composite\n";
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
    //cin >> t; // Uncomment if multiple test cases
    while (t --) {
        solve ();
    } 
    return 0;
}
// thfv