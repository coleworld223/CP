/*
    Problem : 
    given n, sz and an array of size n
    For each window of size 'sz', find the cost to make all elements equal

    Solution : 
    For each window it's most optimal to make every element equal to the median of the window
    For each window we maintain the following things
    1. a multiset of (sz + 1) / 2 smaller elements and their sum (lsum)
    2. a multiset  of (sz / 2) larger elements and their sum (rsum)

    From the above info, ans can be calculated for each window as shown in implementation

*/


#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct ds {
    multiset <ll> l, r;
    ll lsum = 0, rsum = 0;

    void relax () {
        ll tot = l.size() + r.size();
        ll med = (tot + 1) / 2;
        while (l.size() != med) {
            if (l.size() > med) {
                ll x = *l.rbegin();
                lsum -= x;
                rsum += x;
                r.insert (x);
                l.erase (l.find(x));
            }
            else {
                ll x = *r.begin();
                rsum -= x;
                lsum += x;
                l.insert (x);
                r.erase (r.find (x));
            }
        }
    }

    void add (ll x) {
        if (l.empty() || (*l.rbegin()) >= x) {
            l.insert (x);
            lsum += x;
        }
        else {
            r.insert (x);
            rsum += x;
        }
        relax ();
    }

    void rem (ll x) {
        if (l.find (x) != l.end()) {
            l.erase (l.find (x));
            lsum -= x;
        }
        else {
            r.erase (r.find (x));
            rsum -= x;
        }
        relax ();
    }

    array <ll, 3> give () {
        ll med = *l.rbegin();
        return {med, lsum, rsum};
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
            auto [med, l, r] = d.give ();
            ll cntl = (sz + 1) / 2;
            ll ans = (cntl * med - l);
            ans += (r - (sz - cntl) * med);
            res.push_back(ans);
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