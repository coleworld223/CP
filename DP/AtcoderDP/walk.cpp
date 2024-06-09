#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;

ll dp[51][51][64 * 4];

void solve () {
    ll n, k;
    cin >> n >> k;

    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < n; j += 1) {
            ll x; cin >> x;
            if (x == 1) {
                dp[i][j][0] = 1;
            }
        }
    }

    queue <ll> q;

    set <ll> st;

    q.push (k);

    st.insert (k);

    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        if (u == 1) continue;
        ll x = (u / 2);
        if (st.count (x) == 0) {
            st.insert (x);
            q.push (x);
        }
        if (u % 2 != 0) {
            x += 1;
            if (st.count (x) == 0) {
                st.insert (x);
                q.push (x);
            }
        }
    }

    vector <ll> tmp;

    for (ll x : st) {
        tmp.push_back(x);
    }

    map <ll, ll> cmp;

    ll _ = 0;

    for (ll i = 0; i < tmp.size(); i += 1) {
        cmp[tmp[i]] = _++;
    }

    for (ll i = 1; i < tmp.size(); i += 1) {
        ll k1 = tmp[i];
        if (k1 % 2 == 0) {
            ll kp = (k1 / 2);
            ll d1 = cmp[k1], d2 = cmp[kp];
            for (ll x = 0; x < n; x += 1) {
                for (ll y = 0; y < n; y += 1) {
                    for (ll z = 0; z < n; z += 1) {
                        dp[x][y][d1] += (dp[x][z][d2] * dp[z][y][d2]);
                        dp[x][y][d1] %= mod;
                    }
                }
            }
        }
        else {
            ll kp = (k1 / 2), kp2 = (kp + 1);
            ll d1 = cmp[k1], d2 = cmp[kp], d3 = cmp[kp2];
            for (ll x = 0; x < n; x += 1) {
                for (ll y = 0; y < n; y += 1) {
                    for (ll z = 0; z < n; z += 1) {
                        dp[x][y][d1] += (dp[x][z][d2] * dp[z][y][d3]);
                        dp[x][y][d1] %= mod;
                    }
                }
            }
        }
    }

    ll res = 0;

    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < n; j += 1) {
            res += dp[i][j][cmp[k]];
            res %= mod;
        }
    }

    cout << res << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int no_of_tests = 1;
    // cin >> no_of_tests;
    for (int test_no = 0; test_no < no_of_tests; test_no += 1) {
        solve ();
    }
}