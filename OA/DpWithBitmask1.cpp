#include <bits/stdc++.h>
using namespace std;

int solve(int x, int y, vector <vector <int>> r, int k) {
    using ll = long long;
    ll n = r.size();
    ll inf = 1e18;
    auto dis = [&] (ll x1, ll y1, ll x2, ll y2) -> ll {
        return abs(x1 - x2) + abs(y1 - y2);
    };

    vector <vector <ll>> minCost ((1 << n), vector <ll> (n, inf));
    vector <ll> minC (1 << n, inf);

    for (ll msk = 0; msk < (1 << n); msk++) {
        if (__builtin_popcount(msk) == 1) {
            ll bit = __builtin_ctz(msk);
            minCost[msk][bit] = 2 * dis(r[bit][0], r[bit][1], x, y);
            minC[msk] = min(minC[msk], minCost[msk][bit]);
        }
        else {
            for (ll en = 0; en < n; en++) if (msk >> en & 1) {
                ll submsk = (msk ^ (1 << en));
                for (ll nen = 0; nen < n; nen++) if (submsk >> nen & 1) {
                    minCost[msk][en] = min (minCost[msk][en], minCost[submsk][nen] 
                        - dis(x, y, r[nen][0], r[nen][1]) + dis(r[nen][0], r[nen][1], r[en][0], r[en][1])
                        + dis(x, y, r[en][0], r[en][1]));
                }
                minC[msk] = min(minC[msk], minCost[msk][en]);
            }
        }
    }

    vector <vector <ll>> dp (1 << n, vector <ll> (k + 1, inf));

    dp[0][0] = 0;
    ll ans = inf;

    for (ll msk = 0; msk < (1 << n); msk++) {
        for (ll s = msk; s > 0; s = ((s - 1) & msk)) {
            for (ll cnt = 1; cnt <= k; cnt++) {
                dp[msk][cnt] = min(dp[msk][cnt], dp[(msk ^ s)][cnt - 1] + minC[s]);
                if (msk == (1 << n) - 1) {
                    ans = min(ans, dp[msk][cnt]);
                }
            }
        }
    }

    return ans;
}

int main() {
    int x, y;
    cin >> x >> y;
    int k;
    cin >> k;

    int n;
    cin >> n;

    vector <vector <int>> r (n, vector <int> (2));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> r[i][j];
        }
    }

    cout << solve(x, y, r, k) << '\n';
}