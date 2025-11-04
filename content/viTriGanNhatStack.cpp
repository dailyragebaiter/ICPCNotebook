#include <bits/stdc++.h>

#define task   "BriantheCrab"

#define ll     long long
#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())

using namespace std;

template <class T> void mini (T &t, T f) {if (t > f) t = f;}
template <class T> void maxi (T &t, T f) {if (t < f) t = f;}

const int maxN = 1e5 + 5;
const int inf = 1e9 + 7;
const int mod = 1e9 + 7;

int a[maxN];
int l[maxN];

void Solve () {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    stack <int> st;
    for (int i = 1; i <= n; i ++) {
        while (!st.empty () && a[st.top ()] >= a[i]) {
            st.pop ();
        }
        if (!st.empty ()) {
            l[i] = st.top ();
        }
        st.push (i);
    }
    for (int i = 1; i <= n; i ++) {
        cout << l[i] << ' ';
    }    
    return;
}

signed main () {
    cin.tie (nullptr) -> sync_with_stdio (false);
    if (fopen (task".inp", "r")) {
        freopen (task".inp", "r", stdin);
        freopen (task".out", "w", stdout);
    }
    int t = 1;
    //cin >> t;
    while (t --) {
        Solve ();
    } 
    return 0;
}
// Belligerent :)