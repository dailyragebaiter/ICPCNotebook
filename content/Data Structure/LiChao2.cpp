struct Line {
    int a, b;
    
    Line () : a (0), b (inf) {}
    Line (int a, int b) : a (a), b (b) {}
    
    int calc (int x) {
        return a * x + b;
    }
};

struct LiChao {
    vector <Line> lc;
    
    void init (int n) {
        lc.resize (n * 4, Line ());
    }
    
    void upd (int id, int l, int r, Line L) {
        int mid = (l + r) >> 1;
        bool left = L.calc (l) < lc[id].calc (l);
        bool m = L.calc (mid) < lc[id].calc (mid);
        if (m) {
            swap (lc[id], L);
        }
        if (l == r) {
            return;
        }
        if (left != m) {
            upd (id * 2, l, mid, L);
        }
        else {
            upd (id * 2 + 1, mid + 1, r, L);
        }
    }
    
    int get (int id, int l, int r, int x) {
        if (l == r) {
            return lc[id].calc (x);
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            return min (lc[id].calc (x), get (id * 2, l, mid, x));
        }
        return min (lc[id].calc (x), get (id * 2 + 1, mid + 1, r, x));
    }
};

LiChao T;
int h[maxN], w[maxN];
int dp[maxN];
int pfs[maxN];

int p1 (int x) {
    return - 2 * h[x];
}

int p2 (int x) {
    return dp[x] + h[x] * h[x] - w[x];
}

int p3 (int x) {
    return h[x] * h[x] + w[x - 1];
}

void solve () {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> h[i];
    }
    for (int i = 1; i <= n; i ++) {
        cin >> w[i];
        w[i] += w[i - 1];
    }
    T.init (maxN + 1);
    dp[1] = 0;
    T.upd (1, 0, maxN, {p1 (1), p2 (1)});
    for (int i = 2; i <= n; i ++) {
        dp[i] = T.get (1, 0, maxN, h[i]) + p3 (i);
        T.upd (1, 0, maxN, {p1 (i), p2 (i)});
    }
    cout << dp[n];
    return;
}