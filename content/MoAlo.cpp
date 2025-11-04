#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int block_size = 320;

int n, q;
int cnt[N], res[N];
int a[N], ans[N];

struct QUE {
    int l, r, x, id;
} que[N];

bool cmp(QUE A, QUE B) {
    if (A.l / block_size != B.l / block_size)
        return A.l / block_size < B.l / block_size;
    return A.r < B.r;
}

void add(int index) {
    int val = a[index];
    if (cnt[val] > 0) {
        res[cnt[val]]--;
    }
    cnt[val]++;
    res[cnt[val]]++;
}

void remove(int index) {
    int val = a[index];
    res[cnt[val]]--;
    cnt[val]--;
    if (cnt[val] > 0) {
        res[cnt[val]]++;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        que[i] = {l - 1, r - 1, x, i};
    }
    sort(que, que + q, cmp);
    int curr_l = 0, curr_r = -1;
    for (int i = 0; i < q; i++) {
        int l = que[i].l, r = que[i].r, x = que[i].x;
        while (curr_r < r) {
            add(++curr_r);
        }
        while (curr_r > r) {
            remove(curr_r--);
        }
        while (curr_l < l) {
            remove(curr_l++);
        }
        while (curr_l > l) {
            add(--curr_l);
        }
        ans[que[i].id] = res[x];
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}