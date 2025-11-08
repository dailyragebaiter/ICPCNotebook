struct Line {
    int a, b;
    
    Line () : a (0), b (-inf) {}
    Line (int a, int b) : a (a), b (b) {}
    
    inline int get (int x) {
        return a * x + b;
    } 
};

struct Node {
    Line val;
    Node *l, *r;
    
    Node () {
        val = Line ();
        l = r = nullptr;
    }
};

struct LiChao {
    int L, R;
    Node *root;
    
    void init (int l, int r) {
        L = l;
        R = r;
        root = new Node ();
    }
    
    void upd (Node *&cur, int l, int r, Line nw) {
        if (!cur) {
            cur = new Node ();
        }
        int mid = (l + r) >> 1;
        bool left = nw.get (l) > cur -> val.get (l);
        bool m = nw.get (mid) > cur -> val.get (mid);
        if (m) {
            swap (cur -> val, nw);
        }
        if (l == r) {
            return;
        }
        if (left != m) {
            upd (cur -> l, l, mid, nw);
        }
        else {
            upd (cur -> r, mid + 1, r, nw);
        }
    }
    
    int get (Node *cur, int l, int r, int x) {
        if (!cur) {
            return -inf;
        }
        int res = cur -> val.get (x);
        if (l == r) {
            return res;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            return max (res, get (cur -> l, l, mid, x));
        }
        return max (res, get (cur -> r, mid + 1, r, x));
    }
    
    void addLine (Line nw) {
        upd (root, L, R, nw);
    }
    
    int query (int x) {
        return get (root, L, R, x);
    }
};

int n;
int a[maxN];
LiChao T1, T2;
int s[maxN], sl[maxN], sr[maxN];

void solve () {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i] * i;
        sl[i] = sl[i - 1] + a[i] * (i - 1);
        sr[i] = sr[i - 1] + a[i] * (i + 1);
    }
    T1.init (-1e9, 1e9);
    T2.init (-1e9, 1e9);
    int res = s[n];
    for (int i = 1; i <= n; i ++) {
        int p3 = s[n] - s[i] + sl[i];
        int p12 = T1.query (i);
        if (p12 != -inf) {
            maximize (res, p3 + p12);
        }
        T1.addLine ({a[i], s[i - 1] - sl[i]});
    }
    for (int i = n; i >= 1; i --) {
        int p3 = s[n] + s[i - 1] - sr[i - 1];
        int p12 = T2.query (i);
        if (p12 != -inf) {
            maximize (res, p3 + p12);
        }
        T2.addLine ({a[i], sr[i - 1] - s[i]});
    }
    cout << res;
    return;
}