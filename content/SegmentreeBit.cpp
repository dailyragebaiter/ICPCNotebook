#include <bits/stdc++.h>

#define task   "BriantheCrab"

#define int     long long
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

int n, q;
int a[maxN], p[30];

inline bool bit (int x, int i) {
    return ((x >> i) & 1);
}
 
inline int flip (int x) {
    return (1 - x);
}

struct ST {
    int st[maxN * 6], lazy[maxN * 6];
    
    ST () {
        memset (st, 0, szf (st));
    };
    
    void push (int id, int l, int r, int mid) {
        int t = lazy[id];
        if (t == 1) {
            lazy[id * 2] = flip (lazy[id * 2]);
            st[id * 2] = mid - l + 1 - st[id * 2];
            lazy[id * 2 + 1] = flip (lazy[id * 2 + 1]);
            st[id * 2 + 1] = r - mid - st[id * 2 + 1];
        }
        lazy[id] = 0;
    }
    
    void upd (int id, int l, int r, int u, int v) {
        if (v < l || u > r) {
            return;
        }
        if (u <= l && r <= v) {
            lazy[id] = flip (lazy[id]);
            st[id] = r - l + 1 - st[id];
            return;
        }
        int mid = (l + r) >> 1;
        push (id, l, r, mid);
        upd (id * 2, l, mid, u, v);
        upd (id * 2 + 1, mid + 1, r, u, v);
        st[id] = st[id * 2] + st[id * 2 + 1];
    }
    
    int get (int id, int l, int r, int u, int v) {
        if (v < l || r < u) {
            return 0;
        }
        if (u <= l && r <= v) {
            return st[id];
        }
        int mid = (l + r) >> 1;
        push (id, l, r, mid);
        int tL = get (id * 2, l, mid, u, v);
        int tR = get (id * 2 + 1, mid + 1, r, u, v);
        return (tL + tR);
    }
} T[30];

void Solve () {
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        for (int j = 0; j < 30; j ++) {
            if (bit (a[i], j) == 1) {
                p[j] ^= 1;
            }
            if (p[j]) {
                T[j].upd (1, 1, n, i, i);
            }
        }
    }
    while (q --) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            for (int j = 0; j < 30; j ++) {
                if (bit (x, j) != bit (a[i], j)) {
                    T[j].upd (1, 1, n, i, n);
                }
            }
            a[i] = x;
        }
        else {
            int l, r;
            cin >> l >> r;
            int res = 0;
            for (int j = 0; j < 30; j ++) {
                int tmp = T[j].get (1, 1, n, max (l - 1, 1LL), r);
                res += tmp * (r - l + 2 - tmp) * (1 << j);
            }
            cout << res << '\n';
        }
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
        Solve ();
    } 
    return 0;
}
// Belligerent :)