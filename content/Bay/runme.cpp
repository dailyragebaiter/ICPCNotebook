#include <bits/stdc++.h>

#define int long long

using namespace std;

void Solve () {
    int cnt = 0;
    while (true) {
        system ("./gen");
        system ("./main");
        system ("./brute");
        if (system ("diff task.out task.ans > /dev/null")) {
            cout << "sad";
            return;
        }
        else {
            cout << "AC on test " << ++cnt << endl;
        }
    }
}

signed main () {
    ios_base :: sync_with_stdio (0);
    //cin.tie (0);
    int t = 1;
    // cin >> t;
    while (t --) {
        Solve ();
    }
    return 0;
}
