struct Fenwick2D {
    int m, n;
    vector <vector <int>> bit[4];
    
    inline void init (int _m, int _n) {
        m = _m;
        n = _n;
        for (int i = 0; i < 4; i ++) {
            bit[i].resize (m + 4, vector <int> (n + 4, 0));
        } 
    }
    
    inline void upd (int x, int y, int v) {
        for (int i = x; i <= m; i += i & (-i)) {
            for (int j = y; j <= n; j += j & (-j)) {
                bit[0][i][j] += v;
                bit[1][i][j] += x * v;
                bit[2][i][j] += y * v;
                bit[3][i][j] += x * y * v;
            }
        }
    }
    
    inline int get (int x, int y) {
        int res = 0;
        for (int i = x; i; i -= i & (-i)) {
            for (int j = y; j; j -= j & (-j)) {
                res += (x + 1) * (y + 1) * bit[0][i][j] - (y + 1) * bit[1][i][j] 
                - (x + 1) * bit[2][i][j] + bit[3][i][j];
            }
        }
        return res;
    }
    
    inline void updR (int x1, int y1, int x2, int y2, int v) {
        upd (x1, y1, v);
        upd (x1, y2 + 1, -v);
        upd (x2 + 1, y1, -v);
        upd (x2 + 1, y2 + 1, v);
    } 
    
    inline int getR (int x1, int y1, int x2, int y2) {
        return get (x2, y2) - get (x1 - 1, y2) - get (x2, y1 - 1) + get (x1 - 1, y1 - 1);
    }
} T;