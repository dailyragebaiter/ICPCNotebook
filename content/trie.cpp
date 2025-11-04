#include <bits/stdc++.h>

#define task   "brianthecrab"

#define int    long long
#define pii    pair <int, int>
#define fi     first
#define se     second
#define szf    sizeof
#define sz(s)  (int)((s).size())
#define all(v) (v).begin(), (v).end()

using namespace std;

template <class T> void mini (T &t, T f) {if (t > f) t = f;}
template <class T> void maxi (T &t, T f) {if (t < f) t = f;}

const int N = 1e5 + 5;
const int inf = 1e18 + 7;
const int mod = 1e9 + 7;
const int maxNode = 2e6 + 10;

struct Trie {
    struct Node {
        int child[26];
        int ex, cnt;  
    } nodes[maxNode + 10];
    
    int cur;
    
    Trie () : cur (0){
        memset (nodes[0].child, -1, szf (nodes[cur].child));
        nodes[0].cnt = nodes[0].ex = 0;
    };
    
    int newNode () {
        cur ++;
        memset (nodes[cur].child, -1, szf (nodes[cur].child));
        nodes[cur].ex = nodes[cur].cnt = 0;
        return cur;
    }
    
    void addString (string s) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) {
                nodes[pos].child[c] = newNode ();
                //cout << f << ' ' << pos << '\n';
            } 
            pos = nodes[pos].child[c];
            nodes[pos].cnt ++;
        }
        nodes[pos].ex ++;
    }
    
    bool find (string s) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) {
                //cout << s << ' ' << f << '\n';
                return 0;
            }
            pos = nodes[pos].child[c];
        }
        return 1;
    }
} T;

string a[N];

signed main () {
    ios_base :: sync_with_stdio (0);
    cin.tie (0);
    cout.tie (0);
    if (fopen (task".inp", "r")) {
        freopen (task".inp", "r", stdin);
        freopen (task".out", "w", stdout);
    }
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    sort (a + 1, a + n + 1);
    for (int i = n; i >= 1; i --) {
        string s = a[i];
        if (T.find (s)) {
            cout << "YES";
            return 0;
        }
        T.addString (s);
    }
    cout << "NO";
    return 0;
}
// hmvncvdqdela