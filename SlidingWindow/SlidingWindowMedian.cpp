#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct ds {
    multiset <ll> l, r;

    void relax () {
        ll tot = l.size() + r.size();
        ll med = (tot + 1) / 2;
        while (l.size() != med) {
            if (l.size() > med) {
                r.insert (*l.rbegin());
                l.erase (l.find(*l.rbegin()));
            }
            else {
                l.insert (*r.begin());
                r.erase (r.begin());
            }
        }
    }

    void add (ll x) {
        if (l.empty() || (*l.rbegin()) >= x) l.insert (x);
        else r.insert (x); 
        relax ();
    }

    void rem (ll x) {
        if (l.find (x) != l.end()) l.erase (l.find (x));
        else r.erase (r.find (x));
        relax ();
    }

    ll give () {
        ll x = *l.rbegin();
        return x;
    }
};

void solve () {
    ll n, sz;
    cin >> n >> sz;

    vector <ll> a (n), res;

    for (ll i = 0; i < n; i += 1) {
        cin >> a[i];
    }

    ds d;

    for (ll i = 0, j = 0, sm = 0; i < n; i += 1) {
        d.add (a[i]);
        while (i - j + 1 > sz) d.rem (a[j++]);
        if (i - j + 1 == sz) {
            res.push_back(d.give());
        }
    } 

    for (ll x : res) {
        cout << x << ' ';
    }
    cout << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}