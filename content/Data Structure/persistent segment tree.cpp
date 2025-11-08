struct PST {
    struct Node {
        int l, r, val;
    };

    vector<Node> seg;
    vector<int> root;

    PST(int n = 0) {
        seg.reserve(40 * n);
    }

    int build(int l, int r) {
        int id = seg.size();
        seg.push_back({-1, -1, 0});
        if (l == r) return id;
        int m = (l + r) / 2;
        seg[id].l = build(l, m);
        seg[id].r = build(m + 1, r);
        return id;
    }

    int update(int prv, int l, int r, int pos, int val) {
        int id = seg.size();
        seg.push_back(seg[prv]);
        if (l == r) {
            seg[id].val += val;
            return id;
        }
        int m = (l + r) / 2;
        if (pos <= m) seg[id].l = update(seg[prv].l, l, m, pos, val);
        else seg[id].r = update(seg[prv].r, m + 1, r, pos, val);
        seg[id].val = seg[seg[id].l].val + seg[seg[id].r].val;
        return id;
    }

    int query(int id, int l, int r, int x, int y) {
        if (x > r || y < l) return 0;
        if (x <= l && r <= y) return seg[id].val;
        int m = (l + r) / 2;
        return query(seg[id].l, l, m, x, y) + query(seg[id].r, m + 1, r, x, y);
    }
};