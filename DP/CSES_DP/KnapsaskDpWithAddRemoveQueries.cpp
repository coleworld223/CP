#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using i64 = long long;
const i32 MOD = 1e9 + 7;

class CountWays {
  i32 maxSum;
  vector <i64> ways;
public:
  CountWays() {}
  CountWays(i32 maxSum) { init(maxSum); }
  void init(i32 siz) {
    this -> maxSum = maxSum;
    ways.resize(maxSum + 1);
    ways[0] = 1;
  }
  void add(i32 x) {
    for (i32 sum = maxSum; sum >= 0; sum--) if (sum >= x) {
      ways[sum] += ways[sum - x];
      ways[sum] %= MOD;
    }
  }
  void remove(i32 x) {
    for (i32 sum = 0; sum <= maxSum; sum++) if (sum >= x) {
      ways[sum] -= ways[sum - x];
      ways[sum] %= MOD;
    }
  }
  i32 ans(i32 reqSum) {
    i32 res = (ways[reqSum] + MOD) % MOD;
    return res;
  }
};

void solve() {
  i32 siz;
  i32 qryCnt;
  cin >> siz >> qryCnt;

  const i32 maxSum = 5000;
  CountWays Util(maxSum);

  vector <i32> A (siz);
  for (i32 i = 0; i < siz; ++i) {
    cin >> A[i];
    Util.add(A[i]);
  }

  vector <i32> res;
  while (qryCnt--) {
    char qryType;
    cin >> qryType;

    if (qryType == '=') {
      i32 reqSum;
      cin >> reqSum;
      res.push_back(Util.ans(reqSum));
    }
    else {
      i32 ele;
      cin >> ele;
      qryType == '+' ? Util.add(ele) : Util.remove(ele);
    }
  } 

  for (i32 x : res) {
    cout << x << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(0);cin.tie(0);
  i32 T = 1;
  // cin >> T;
  for (i32 i = 0; i < T; ++i) {
    solve();
  }
}
