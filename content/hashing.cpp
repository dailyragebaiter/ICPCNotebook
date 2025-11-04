#include <bits/stdc++.h>
using namespace std;
#define int long long

const int base = 31;
const int mod1 = 111539786;
const int maxn = 1e6 + 5;

int h1[maxn], mu1[maxn];
string s, t;
vector<int> ans;

int gh(int l, int r) {
    return (h1[r] - h1[l - 1] * mu1[r - l + 1] % mod1 + mod1) % mod1;
}

signed main() {
    cin >> s >> t;
    s = " " + s;
    mu1[0] = 1;
    for (int i = 1; i < s.size(); i ++) {
        h1[i] = (h1[i - 1] * base + (s[i] - 'a' + 1)) % mod1;
        mu1[i] = (mu1[i - 1] * base) % mod1;
    }
    int hasht = 0;
    for (int i = 0; i < t.size(); i ++) {
        hasht = (hasht * base + (t[i] - 'a' + 1)) % mod1;
    }
    for (int i = 1; i < s.size() - t.size() + 1; i ++) {
        int h1 = gh(i, i + t.size() - 1);
        if (hasht == h1) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << '\n';
    return 0;

}