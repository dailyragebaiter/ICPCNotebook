#include <bits/stdc++.h>

#define task   "BriantheCrab"

#define int    long long
#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())

using namespace std;

template <class T> void mini (T &t, T f) {if (t > f) t = f;}
template <class T> void maxi (T &t, T f) {if (t < f) t = f;}

const int maxN = 1e5 + 5;
const int inf = 1e18 + 7;
const int mod = 1e9 + 7;

struct ST {
    vector <int> st, lazy;
    
    void init (int n) {
        st.assign (n * 6, 0);
        lazy.assign (n * 6, 0);
    }
    
    void push (int id, int l, int r, int mid) {
        int t = lazy[id];
            if (t != 0) {
            st[id * 2] += (mid - l + 1) * t;
            lazy[id * 2] += t;
            st[id * 2 + 1] += (r - (mid + 1) + 1) * t;
            lazy[id * 2 + 1] += t;
        }
        lazy[id] = 0;
    }
    
    void upd (int id, int l, int r, int u, int v, int val) {
        if (v < l || u > r) {
            return;
        }
        if (u <= l && r <= v) {
            st[id] += (r - l + 1) * val;
            lazy[id] += val;
            return;
        }
        int mid = (l + r) >> 1;
        push (id, l, r, mid);
        upd (id * 2, l, mid, u, v, val);
        upd (id * 2 + 1, mid + 1, r, u, v, val);
        st[id] = st[id * 2] + st[id * 2 + 1];
    }
    
    int get (int id, int l, int r, int u, int v) {
        if (v < l || u > r) {
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
};

int n, q;
int a[maxN];
ST T;

void print () {
    for (int i = 1; i <= n; i ++) {
        cout << T.get (1, 1, n, i, i) << ' ';
    }
    cout << '\n';
}

void solve () {
    cin >> n >> q;
    T.init (n);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        T.upd (1, 1, n, i, i, a[i]);
    }
    //print ();
    while (q --) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            int x;
            cin >> x;
            T.upd (1, 1, n, l, r, x);
            //print ();
        }
        else {
            cout << T.get (1, 1, n, l, r) << '\n';
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
// thfdgb