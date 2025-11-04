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

const int maxN = 2e3 + 5;
const int inf = 1e9 + 7;
const int mod = 1e9 + 7;
const int hx[4] = {-1, 0, 1, 0};
const int hy[4] = {0, -1, 0, 1};

int a[maxN][maxN];
int d[maxN][maxN][4];

struct Data {
    int x, y, dir;
};

void bfs () {
    deque <Data> q;
    q.push_front ({1, 1, 2});
    d[1][1][2] = 0;
    while (!q.empty ()) {
        auto [u, v, dir] = q.front ();
        q.pop_front ();
        //cout << u << ' ' << v << ' ' << dir << ' ' << d[u][v][dir] << '\n';
        for (int k = 0; k < 4; k ++) {
            int x = u + hx[k];
            int y = v + hy[k];
            int dirl = k;
            //cout << a[x][y] << '\n';
            if (a[x][y]) {
                if (dirl == dir) {
                    if (d[x][y][dirl] > d[u][v][dir]) {
                        d[x][y][dirl] = d[u][v][dir];
                        q.push_front ({x, y, dirl});
                    }
                }
                else if (dirl % 2 != dir % 2) {
                    if (d[u][v][dirl] > d[u][v][dir] + 1) {
                        d[u][v][dirl] = d[u][v][dir] + 1;
                        q.push_back ({u, v, dirl});
                    }
                }
            }
        }
    }
}

void Solve () {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            char c;
            cin >> c;
            a[i][j] = (c == '.');
            for (int k = 0; k <= 3; k ++) {
                d[i][j][k] = inf;
            }
        }
    }
    bfs ();
    int res = inf;
    for (int k = 0; k < 4; k ++) {
        mini (res, d[n][n][k]);
        //cout << d[n][n][k] << ' ' << k << '\n';
    }
    cout << ((res == inf) ? -1 : res);
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