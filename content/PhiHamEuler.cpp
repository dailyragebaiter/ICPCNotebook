#include <bits/stdc++.h>

#define task     "EulerPhi" // Đổi tên task cho phù hợp

#define int    long long // int mặc định là long long
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

const int maxN = 2e5 + 5; // Có thể không cần nếu bài toán chỉ tính phi hàm
const int inf = 1e18 + 7;
const int mod = 1e9 + 7; 

// Hàm tính Phi Euler
ll euler_phi (ll n) {
    ll res = n;
    for (ll i = 2; i * i <= n; ++ i) {
        if (n % i == 0) {
            res = res / i * (i - 1); // Áp dụng công thức (1 - 1/p_i)
            while (n % i == 0) {
                n /= i; // Chia n cho tất cả các lũy thừa của i
            }
        }
    }
    // Nếu sau vòng lặp, n vẫn còn > 1, nghĩa là n là một số nguyên tố lớn
    if (n > 1) {
        res = res / n * (n - 1);
    }
    return res;
}

void solve () {
    ll n;
    cin >> n;
    cout << euler_phi (n) << "\n";
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