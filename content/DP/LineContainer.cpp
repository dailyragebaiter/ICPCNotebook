ll divi(ll a, ll b) {
	ll res = (a / b);
	if (a < 0 && b > 0) --res;
	if (a > 0 && b < 0) --res;
	return res;
}

struct LC {
	struct line {
		ll a, b;
		mutable ll p;
		line(ll a_, ll b_, ll p_) : a(a_), b(b_), p(p_) {}
		bool operator<(const line &other) const {
			if (other.a == oo && other.b == oo) return p < other.p;
			return a < other.a;
		}
	};
	multiset<line> mylc;
	bool isect(multiset<line>::iterator x, multiset<line>::iterator y) {
		if (y == mylc.end()) {
			x->p = oo;
			return false;
		}
		if (x->a == y->a) {
			if (x->b > y->b) {
				x->p = oo;
			} else {
				x->p = -oo;
			}
		} else {
			x->p = divi((y->b - x->b), (x->a - y->a));
		}
		return x->p >= y->p;
	}
	void add(ll a, ll b) {
		multiset<line>::iterator x = mylc.insert(line(a, b, 0)), y = next(x);
		while(isect(x, y)) y = mylc.erase(y);
		
		y = x;
		if (x != mylc.begin()) {
			y = prev(y);
			if (isect(y, x)) isect(y, mylc.erase(x));
		}
		while(y != mylc.begin()) {
			x = prev(y);
			if (x->p >= y->p) {
				isect(x, mylc.erase(y));
				y = x;
			} else break;
		}
	}
	ll get(const ll x) {
		multiset<line>::iterator it = mylc.lower_bound(line(oo, oo, x));
		return it->a * x + it-> b;
	}
} lc;