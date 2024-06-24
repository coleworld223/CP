#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int a[10000011];
int cnt[1000001];

void solve () {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i += 1) {
        cin >> a[i];
    }

    int ans = 0;
    array <int, 2> coor = {-1, -1};

    for (int i = 0, j = 0, dis = 0; i < n; i += 1) {
        if (cnt[a[i]] == 0) dis += 1;
        cnt[a[i]] += 1;
        while (dis > k) {
            cnt[a[j]]--;
            if (cnt[a[j]] == 0) dis--;
            j += 1;
        }
        if (i - j + 1 > ans) {
            ans = i - j + 1;
            coor = {j + 1, i + 1};
        }
    }

    cout << coor[0] << ' ' << coor[1] << '\n';
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tests = 1;
    // cin >> tests;

    for (int i = 0; i < tests; i += 1) {
        solve ();
    }
}