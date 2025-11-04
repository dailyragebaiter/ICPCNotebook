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
int V, E;
vector <int> adj[maxN];
int disc[maxN], low[maxN];
bool onStack[maxN];
stack <int> st;
int timer;
int scc_count;

void find_scc (int u) {
    disc[u] = low[u] = ++ timer;
    st.push (u);
    onStack[u] = true;
    
    for (int v : adj[u]) {
        if (disc[v] == -1) { // Not visited
            find_scc (v);
            low[u] = min (low[u], low[v]);
        } else if (onStack[v]) { // Back edge or cross edge to a node in current recursion stack
            low[u] = min (low[u], disc[v]);
        }
    }
    
    if (low[u] == disc[u]) {
        scc_count ++;
        cout << "SCC " << scc_count << ": ";
        int node;
        while (true) {
            node = st.top ();
            st.pop ();
            onStack[node] = false;
            cout << node << " ";
            if (node == u) {
                break;
            }
        }
        cout << '\n';
    }
}

void solve () {
    cin >> V >> E;
    for (int i = 0; i < E; ++ i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
    }
    
    for (int i = 1; i <= V; ++ i) {
        disc[i] = -1;
        low[i] = -1;
        onStack[i] = false;
    }
    timer = 0;
    scc_count = 0;
    
    for (int i = 1; i <= V; ++ i) {
        if (disc[i] == -1) {
            find_scc (i);
        }
    }
    
    cout << "Total SCCs: " << scc_count << '\n';
    
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