struct CHT {
	ll getval(pll X, ll x) {
		return X.a * x + X.b;
	}
	bool bad(pll x, pll y, pll z) {
		return (y.b - x.b) * (x.a - z.a) >= (z.b - x.b) * (x.a - y.a); 
	}
	vector<pll> s;
	void add(ll a, ll b) {
		int m = sze(s);
		while(m >= 2 && bad(s[m - 2], s[m - 1], make_pair(a, b))) {
			s.pop_back();
			--m;
		}
		s.pb(make_pair(a, b));
	}
	ll get(ll x) {
		if (s.empty()) return oo;
		int l = 0, r = sze(s) - 2;
		ll ans = getval(s[l], x);
		while(l <= r) {
			int mid = (l + r) >> 1;
			ll X = getval(s[mid], x);
			ll Y = getval(s[mid + 1], x);
			if (X > Y) {
				l = mid + 1;
			} else {
				r = mid - 1;
			}
			ans = min(ans, min(X, Y));
		}
		return ans;
	}
}