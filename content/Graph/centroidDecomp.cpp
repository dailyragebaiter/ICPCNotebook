int n, k;
int sz[maxN], cnt[maxN], L[maxN];
bool del[maxN];
vector <int> adj[maxN], tmp;
 
void szCal (int u, int p) {
    sz[u] = 1;
    for (auto v : adj[u]) {
        if (v == p || del[v]) {
            continue;
        }
        szCal (v, u);
        sz[u] += sz[v];
    }
}
 
int findCen (int u, int p, int curSz) {
    for (auto v : adj[u]) {
        if (v == p || del[v]) {
            continue;
        }
        if (sz[v] > curSz / 2) {
            return findCen (v, u, curSz);
        }
    }
    return u;
}
 
void calDepth (int u, int p, int curD) {
    if (curD > k && k != -1) { 
        return;
    }
    L[u] = curD;
    tmp.push_back (curD);
    for (int v : adj[u]) {
        if (v != p && !del[v]) {
            calDepth (v, u, curD + 1);
        }
    }
}
 
int cal (int u) {
    szCal (u, 0);
    int rt = findCen (u, 0, sz[u]);
    for (int i = 0; i <= sz[rt]; ++i) {
        cnt[i] = 0;
    }
    cnt[0] = 1;
    int res = 0;
    for (int v : adj[rt]) {
        if (!del[v]) {
            tmp.clear ();
            calDepth (v, rt, 1);
            for (int it : tmp) {
                if (k - it >= 0 && (k - it) <= sz[rt]) {
                    res += cnt[k - it];
                }
            }
            for (int it : tmp) {
                if (it <= sz[rt]) {
                    cnt[it] ++;
                }
            }
        }
    }
    del[rt] = true;
    for (int v : adj[rt]) {
        if (!del[v]) {
            res += cal(v);
        }
    }
    return res;
}
 
void solve () {
    cin >> n >> k;
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
        adj[v].push_back (u);
    }
    cout << cal (1);
    return;
}
