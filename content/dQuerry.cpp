/*Mo comparision
	Chia mang thanh cac block do dai sqrt(N)
	Sort query theo block cua l tang dan, roi toi r tang dan
	Chung minh duoc voi cach sap xep tren thi 
		tong cac chi phi chuyen O(1) tu query[i]->query[i+1] khong qua (N+Q)*sqrt(N)
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;
struct query_t {
	int l, r, idx;
} query[N];

int n, q;
int a[N];
int cnt[N];
int res[N];

void compress(int *a) {
	set<int> s;
	for(int i = 1; i <= n; ++i) s.insert(a[i]);
	vector<int> b(s.begin(), s.end());
	for(int i = 1; i <= n; ++i) {
		a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
	}
}

bool mo_cmp(query_t a, query_t b) {
	static int tmp = sqrt(n);
	if (a.l/tmp != b.l/tmp) return a.l/tmp < b.l/tmp;
	return a.r < b.r;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 0; i < q; ++i) {
		cin >> query[i].l >> query[i].r;
		query[i].idx = i;
	}
	sort(query, query + q, mo_cmp);
	compress(a);

	int ans = 0;
	memset(cnt, 0, sizeof cnt);
	for(int i = query[0].l; i <= query[0].r; ++i) {
		if (cnt[a[i]] == 0) ans++;
		cnt[a[i]]++;
	}
	res[query[0].idx] = ans;
	for(int k = 1; k < q; ++k) {
		if (query[k-1].l < query[k].l) {
			for(int i = query[k-1].l; i < query[k].l; ++i) {
				cnt[a[i]]--;
				if (cnt[a[i]] == 0) ans--;
			}
		} else for(int i = query[k-1].l-1; i >= query[k].l; --i) {
			if (cnt[a[i]] == 0) ans++;
			cnt[a[i]]++;
		}

		if (query[k-1].r > query[k].r) {
			for(int i = query[k-1].r; i > query[k].r; --i) {
				cnt[a[i]]--;
				if (cnt[a[i]] == 0) ans--;
			}
		} else for(int i = query[k-1].r+1; i <= query[k].r; ++i) {
			if (cnt[a[i]] == 0) ans++;
			cnt[a[i]]++;
		} 
		res[query[k].idx] = ans;
	}
	for(int i = 0; i < q; ++i) cout << res[i] << '\n';
	return 0;
}