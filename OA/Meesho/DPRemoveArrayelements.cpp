int solve(vector <int> arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        arr[i]--;
    }
    int ans = 0;
    vector <int> d (n), cnt(n + 5);
    for (int i = 0; i < n; i++) {
        d[i] = (i - arr[i]);
        ans += d[i] == 0;
        if (d[i] >= 0) cnt[d[i]] += 1;
    }

    vector <vector <int>> dp (n + 1, vector <int> (n + 1));
    dp[0][0] = (arr[0] == 0);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i + 1; j++) {
            if (j) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
            dp[i][j] = max(dp[i][j], dp[i - 1][j] + (d[i] == j));
        }
    }

    for (int i = 0; i < n; i++) {
        if (d[i] >= 0) cnt[d[i]]--;
        for (int j = 0; j <= i + 1; j++) {
            ans = max(ans, dp[i][j] + cnt[j]);
        }
    }

    return ans;
} 