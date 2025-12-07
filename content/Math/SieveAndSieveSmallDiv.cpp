
int a[maxN];

namespace Sieve {
    vector <bool> check;
    vector <int> spf;
    
    void calPrime (int lim) {
        check.resize (lim + 1, true);
        check[0] = check[1] = 0;
        for (int i = 2; i * i <= lim; i ++) {
            if (check[i]) {
                for (int j = i * i; j <= lim; j += i) {
                    check[j] = 0;
                }
            }
        }
        return;
    }
    
    void calDiv (int lim) {
        spf.resize (lim + 1);
        for (int i = 1; i <= lim; i ++) {
            spf[i] = i;
        }
        for (int i = 1; i * i <= lim; i ++) {
            if (spf[i] == i) {
                for (int j = i * i; j <= lim; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
        return;
    }
    
    void calFactor (int x, vector <int> &f) {
        while (x > 1) {
            f.push_back (spf[x]);
            x /= spf[x];
        }
        return;
    }
}

void solve () {
    int n;
    cin >> n;
    Sieve :: calPrime (n);
    for (int i = 1; i <= n; i ++) {
        if (Sieve :: check[i]) {
            cout << i << ' ';
        }
    }
    return;
}
