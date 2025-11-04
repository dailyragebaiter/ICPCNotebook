#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m;

bool joint[N];
int timeDfs = 0, brigde = 0;
int low[N], num[N];
vector <int> adj[N];

void dfs (int u, int pre) {
    int child = 0;
    num[u] = low[u] = ++timeDfs;
    for (auto v : adj[u]) {
        if (v == pre) {
            continue;
        }
        if (!num[v]) {
            dfs (v, u);
            low[u] = min (low[v], low[u]);
            if (low[v] == num[v]) {
                brigde ++;
            }
            child ++;
            if (u == pre) {
                if (child > 1) {
                    joint[u] = true;
                }
            }
            else if (low[v] >= num[u]) {
                joint[u] = true;
            }
        }
        else {
            low[u] = min (low[u], num[v]);
        }
    }
}
int main () {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
        adj[v].push_back (u);
    }
    for (int i = 1; i <= n; i ++) {
        if (!num[i]) {
            dfs (i, i);
        }
    }
    int cntjoint = 0;
    for (int i = 1; i <= n; i ++) {
        cntjoint += (joint[i]);
    }
    cout << cntjoint << '\n';
    for (int i = 1; i <= n; i ++) {
        if (joint[i]) cout << i << " ";
    }
}