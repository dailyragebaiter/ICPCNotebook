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

const int maxN = 1005; // maxN for each dimension
const int inf = 1e18 + 7;
const int mod = 1e9 + 7;

int a[maxN][maxN];
int tree[4 * maxN][4 * maxN];
int R, C;

void build_y (int node_x, int lx, int rx, int node_y, int ly, int ry) {
    if (ly == ry) {
        if (lx == rx) {
            tree[node_x][node_y] = a[lx][ly];
        } else {
            tree[node_x][node_y] = tree[2 * node_x][node_y] + tree[2 * node_x + 1][node_y];
        }
        return;
    }
    int my = (ly + ry) / 2;
    build_y (node_x, lx, rx, 2 * node_y, ly, my);
    build_y (node_x, lx, rx, 2 * node_y + 1, my + 1, ry);
    tree[node_x][node_y] = tree[node_x][2 * node_y] + tree[node_x][2 * node_y + 1];
}

void build_x (int node_x, int lx, int rx) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        build_x (2 * node_x, lx, mx);
        build_x (2 * node_x + 1, mx + 1, rx);
    }
    build_y (node_x, lx, rx, 1, 1, C);
}

int query_y (int node_x, int node_y, int ly, int ry, int qly, int qry) {
    if (ly > qry || ry < qly) {
        return 0;
    }
    if (qly <= ly && ry <= qry) {
        return tree[node_x][node_y];
    }
    int my = (ly + ry) / 2;
    int left_sum = query_y (node_x, 2 * node_y, ly, my, qly, qry);
    int right_sum = query_y (node_x, 2 * node_y + 1, my + 1, ry, qly, qry);
    return left_sum + right_sum;
}

int query_x (int node_x, int lx, int rx, int qlx, int qrx, int qly, int qry) {
    if (lx > qrx || rx < qlx) {
        return 0;
    }
    if (qlx <= lx && rx <= qrx) {
        return query_y (node_x, 1, 1, C, qly, qry);
    }
    int mx = (lx + rx) / 2;
    int left_sum = query_x (2 * node_x, lx, mx, qlx, qrx, qly, qry);
    int right_sum = query_x (2 * node_x + 1, mx + 1, rx, qlx, qrx, qly, qry);
    return left_sum + right_sum;
}

void update_y (int node_x, int lx, int rx, int node_y, int ly, int ry, int up_x, int up_y, int val) {
    if (ly == ry) {
        if (lx == rx) {
            tree[node_x][node_y] = val;
        } else {
            tree[node_x][node_y] = tree[2 * node_x][node_y] + tree[2 * node_x + 1][node_y];
        }
        return;
    }
    int my = (ly + ry) / 2;
    if (up_y <= my) {
        update_y (node_x, lx, rx, 2 * node_y, ly, my, up_x, up_y, val);
    } else {
        update_y (node_x, lx, rx, 2 * node_y + 1, my + 1, ry, up_x, up_y, val);
    }
    tree[node_x][node_y] = tree[node_x][2 * node_y] + tree[node_x][2 * node_y + 1];
}

void update_x (int node_x, int lx, int rx, int up_x, int up_y, int val) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        if (up_x <= mx) {
            update_x (2 * node_x, lx, mx, up_x, up_y, val);
        } else {
            update_x (2 * node_x + 1, mx + 1, rx, up_x, up_y, val);
        }
    }
    update_y (node_x, lx, rx, 1, 1, C, up_x, up_y, val);
}

void solve () {
    // Example usage
    cin >> R >> C;
    for (int i = 1; i <= R; ++ i) {
        for (int j = 1; j <= C; ++ j) {
            cin >> a[i][j];
        }
    }

    // Build the 2D Segment Tree
    build_x (1, 1, R);

    // Example queries and updates
    int q;
    cin >> q;
    while (q --) {
        int type;
        cin >> type;
        if (type == 1) { // Query
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            cout << query_x (1, 1, R, r1, r2, c1, c2) << '\n';
        } else { // Update
            int r, c, val;
            cin >> r >> c >> val;
            update_x (1, 1, R, r, c, val);
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