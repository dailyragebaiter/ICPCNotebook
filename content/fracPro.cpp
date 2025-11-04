#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second

const int N = 1e5 + 5;

int n, k;
double u[N], w[N];

bool cmp(pair<double, int> a, pair<double, int> b) {
    return a.fi > b.fi;
}

double check(double val, int trace) {
    vector<pair<double, int>> v;
    for (int i = 1; i <= n; i++) {
        v.push_back({u[i] - val * w[i], i});
    }
    sort(v.begin(), v.end(), cmp);
    int cnt = 0;
    double sum = 0;
    double upper_res = 0, lower_res = 0;
    for (auto ok : v) {
        if (cnt == k) {
            if (trace) {
                return upper_res / lower_res;
            }
            return sum;
        }
        sum += ok.fi;
        upper_res += u[ok.se];
        lower_res += w[ok.se];
        cnt++;
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> u[i] >> w[i];
    }
    double l = 0, r = 1e18;
    double ans = -1;
    while (r - l > 1e-7) { 
        double mid = (l + r) / 2;
        if (check(mid, 0) >= 0) {
            ans = mid;
            l = mid;
        } 
        else {
            r = mid;
        }
    }
    cout << fixed << setprecision(10) << check(ans, 1) << endl;
    return 0;
}