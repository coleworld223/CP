#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct ds {
	set <ll> st;
	void add(ll x) {
		st.insert(x);
	}
	void merge(ds& oth) {
		if (oth.st.size() > st.size()) swap(st, oth.st);
		for (ll x : oth.st) {
			st.insert(x);
		}
	}
};

void solve() {
	ll n;
	cin >> n;

	vector <ll> col (n);
	vector <vector <ll>> a (n);

	for (ll i = 0; i < n; i++) {
		cin >> col[i];
	}

	for (ll i = 0; i < n - 1; i++) {
		ll u, v;
		cin >> u >> v;
		u--; v--;
		a[u].push_back(v);
		a[v].push_back(u);
	}

	ds d[n];

	vector <ll> res (n);

	function <void (ll, ll)> dfs = [&] (ll u, ll p) {
		d[u].add(col[u]);
		for (ll v : a[u]) if (v != p) {
			dfs(v, u);
			d[u].merge(d[v]);
		}
		res[u] = d[u].st.size();
	};

	dfs(0, -1);

	for (ll x : res) {
		cout << x << ' ';
	}
	cout << '\n';
}

int main() {
	ios_base::sync_with_stdio();cin.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i < t; i++) {
		solve();
	}
}