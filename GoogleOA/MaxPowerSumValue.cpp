// Maximize Power Values Sum 🪴
// You are provided with an array containing N power values, each representing a specific power level. 
// Additionally, a value K is given, signifying that choosing a power value X excludes any other power
//  values within the range of X-K to X+K exclude X itself. Your objective is to determine the maximum sum achievable by selecting the optimal power values.



int solve(vector <int> p, int k) {
    using ll = long long;
    ll n = p.size();
    vector <ll> dp (n);
    multiset <ll> st;
    st.insert(0);
    ll ans = 0, mx = 0;

    for (ll i = 0; i < n; i++) {
        if (i - k >= 0) mx = max(mx, dp[i - k]);
        dp[i] = p[i] + mx;
        ans = max(ans, dp[i]);
    }

    return ans;
}