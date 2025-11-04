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

struct Segment {
    int l, r, id;
};

struct ST {
    int st[maxN * 4];
    
    ST () {
        memset (st, 0, szf (st));      
    };
    
    void upd (int id, int l, int r, int pos, int val) {
        if (pos < l || pos > r) {
            return;
        }
        if (l == r) {
            st[id] += val;
            return;
        }
        int mid = (l + r) >> 1;
        upd (id * 2, l, mid, pos, val);
        upd (id * 2 + 1, mid + 1, r, pos, val);
        st[id] = st[id * 2] + st[id * 2 + 1];
        return;
    }
    
    int get (int id, int l, int r, int u, int v) {
        if (v < l || u > r) {
            return 0;
        }
        if (u <= l && r <= v) {
            return st[id];
        }
        int mid = (l + r) >> 1;
        int tL = get (id * 2, l, mid, u, v);
        int tR = get (id * 2 + 1, mid + 1, r, u, v);
        return (tL + tR);
    }
};

int res[maxN];
vector <Segment> seg;
ST T;

bool cmp (Segment A, Segment B) {
    if (A.l == B.l) {
        return A.r > B.r;
    }
    return A.l < B.l;
}

void Solve () {
    int n;
    cin >> n;
    int mx = 0;
    for (int i = 1; i <= n; i ++) {
        int l, r;
        cin >> l >> r;
        maxi (mx, r);
        seg.push_back ({l, r, i});
    }
    sort (seg.begin (), seg.end (), cmp);
    int i = 0;
    while (i < seg.size ()) {
        auto [x, y, id] = seg[i];
        int j = i + 1, cnt = 1;
        while (0 <= j && j < seg.size ()) {
            if (seg[j].l != x || seg[j].r != y) {
                break;
            }
            cnt ++;
            j ++;
        }
        int add = T.get (1, 1, mx, y, mx) + cnt - 1;
        for (int k = i; k <= j - 1; k ++) {
            res[seg[k].id] = add;
        }
        T.upd (1, 1, mx, y, cnt);
        i = j;
    }
    for (int i = 1; i <= n; i ++) {
        cout << res[i] << '\n';
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