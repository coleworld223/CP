using i64 = long long;
using i32 = int;
const i64 MOD = 1e9 + 7;
class Math {
  i32 N;
  vector <i64> F;
  vector <i64> iF;
public:
  void init(i32 N) {
    this -> N = N;
    F.resize(N + 1);
    iF.resize(N + 1);
    work();
  }
  void work() {
    F[0] = iF[0] = 1;
    for (i64 i = 1; i <= N; ++i) {
      F[i] = (F[i - 1] * i) % MOD;
      iF[i] = inv(F[i]);
    }
  }
  i64 P(i64 a, i64 b) {
    i64 res = 1;
    i64 mul = a;
    while (b) {
      if (b & 1) res *= mul;
      mul *= mul;
      res %= MOD;
      mul %= MOD;
      b >>= 1;
    }
    return res;
  }
  i64 inv(i64 a) {
    return P(a, MOD - 2);
  }
  i64 C(i64 n, i64 r) {
    if (r > n) return 0ll;
    i64 res = (((F[n] * iF[r]) % MOD) * iF[n - r]) % MOD;
    return res;
  }
};
