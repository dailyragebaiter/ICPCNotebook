struct Point {
    ld x, y;
};
Point sub (Point A, Point B) {
    return {A.x - B.x, A.y - B.y};
}
ld cross (Point A, Point B, Point C) {
    Point AB = sub (B, A);
    Point AC = sub (C, A);
    return AB.x * AC.y - AB.y * AC.x;
}
ld dot (Point A, Point B, Point C) {
    Point AB = sub (B, A);
    Point AC = sub (C, A);
    return AB.x * AC.x + AB.y * AC.y;
}
bool onSeg (Point P, Point Q, Point R) {
    bool t1 = min (P.x, Q.x) - Eps <= R.x && R.x <= max (P.x, Q.x) + Eps;
    bool t2 = min (P.y, Q.y) - Eps <= R.y && R.y <= max (P.y, Q.y) + Eps;
    return (t1 & t2);
}
int n, m;
Point a[maxN];
int check (Point Q) {
    for (int i = 1; i <= n; i ++) {
        if (cross (a[i], a[i + 1], Q) == 0 && onSeg (a[i], a[i + 1], Q)) {
            return 2;
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i ++) {
        Point P1 = a[i];
        Point P2 = a[i + 1];
        if (P1.y > P2.y) {
            swap (P1, P2);
        }        
        if (P1.y <= Q.y && Q.y < P2.y) {
            ll cp = cross (P1, P2, Q);
            if (cp > 0) {
                ++ res;
            }
        }
    }
    if (res % 2 == 1) {
        return 1; 
    }
    return 0;
}
inline void Solve () {
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i].x >> a[i].y;
    }
    a[n + 1] = a[1];
    for (int i = 1; i <= m; i ++) {
        Point ok;
        cin >> ok.x >> ok.y;
        int sad = check (ok);
        if (sad == 1) {
            cout << "INSIDE\n";
        }
        else if (sad == 2) {
            cout << "BOUNDARY\n";
        }
        else {
            cout << "OUTSIDE\n";
        }
    }
    return;
}