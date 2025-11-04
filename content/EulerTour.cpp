#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> adj[N];
int m = 0, root = 1;
int tour[2 * N], en[N], st[N], delta[2 * N], result[N];

void dfs(int u, int parent_of_u) {
    st[u] = ++m;
    tour[m] = u;
    for (int v : adj[u]) {
        if (v != parent_of_u) {
            dfs(v, u);
        }
    }
    en[u] = m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n, q;
    cin >> n >> q;
    int u, v, x;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(root, 0);

    while (q--) {
        cin >> u >> x;
        delta[st[u]] += x;
        delta[en[u] + 1] -= x;
    }

    int current_value = 0;
    for (int i = 1; i <= m; i++) {
        current_value += delta[i];
        result[tour[i]] += current_value;
    }

    for (int i = 1; i <= n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}