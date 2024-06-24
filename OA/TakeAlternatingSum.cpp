#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
    given a seq of n integers  {1, 2, ... , n}
    keep removing alternating elements from start to end and add them to a sum
    till more that one element is left if array
    find the tot sum
*/

int main () {
    ll n;
    cin >> n;

    ll sub = (1 << (31 - __builtin_clz (n)));

    ll res = n * (n + 1) / 2;
    cout << res - sub << '\n';
}