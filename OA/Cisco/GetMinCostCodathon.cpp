#include <bits/stdc++.h>
using namespace std;

/*
    Three servers are to be made using a shift cost and arbitrary ammount of increase and decrease operations
*/

int getMinCost(vector <int> c, vector <int> f, int cst) {
    int n = c.size();
    sort (f.begin(), f.end());
    int ans = 0;
    for (int x : f) ans += x;

    function <void (int, int, int, vector <int>&)> dfs = [&] (int idx, int msk, int tot, vector <int> &tmp) {
        if (idx >= n) {
            int res = tot;
            vector <int> t = tmp;
            sort (t.begin(), t.end());
            for (int i = 0; i < 3; i += 1) {
                res += abs (t[i] - f[i]);
            }
            ans = min (ans, res);
            return;
        }
        if (msk >> idx & 1) {
            dfs(idx + 1, msk, tot, tmp);
            return;
        }
        dfs(idx + 1, msk, tot, tmp);
        for (int i = 0; i < 3; i += 1) {
            tmp[i] += c[idx];
            dfs(idx + 1, msk, tot + cst, tmp);
            tmp[i] -= c[idx];
        } 
    };

    for (int msk = 0; msk < (1 << n); msk++) if (__builtin_popcount(msk) == 3) {
        vector <int> tmp;
        for (int i = 0; i < n; i += 1) if (msk >> i & 1) {
            tmp.push_back(c[i]);
        }
        dfs(0, msk, 0, tmp);
    }

    return ans;
}



int main() {
    int n, cst;
    cin >> n >> cst;

    vector <int> c (n), f (3);

    for (int i = 0; i < n; i += 1) {
        cin >> c[i];
    }

    for (int i = 0; i < 3; i += 1) {
        cin >> f[i];
    }

    cout << getMinCost(c, f, cst) << '\n';
}