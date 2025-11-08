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
const int mod = 1e9 + 7;

int a[maxN];
vector <int> adj[maxN];
int V1, V2, E;
int match_v[maxN];
bool visited[maxN];

bool dfs_augment (int u) {
    for (int v : adj[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (match_v[v] == 0 || dfs_augment (match_v[v])) {
                match_v[v] = u;
                return true;
            }
        }
    }
    return false;
}

void solve () {
    cin >> V1 >> V2 >> E;
    for (int i = 0; i < E; ++ i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
    }
    
    int matching_size = 0;
    for (int u = 1; u <= V1; ++ u) {
        for (int i = 1; i <= V2; ++ i) {
            visited[i] = false;
        }
        if (dfs_augment (u)) {
            matching_size ++;
        }
    }
    
    cout << matching_size << '\n';
    
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