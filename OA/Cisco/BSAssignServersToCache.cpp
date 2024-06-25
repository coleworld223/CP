int solve (int n, vector <int> c) {
    vector <int> cnt (n);
    int mx = 0;
    for (int i = 0; i < c.size(); i += 1) {
        c[i]--;
        cnt[c[i]] += 1;
    }

    int lo = 0, hi = 1e8;

    auto chk = [&] (int mid) -> bool {
        long long sp = 0, lft = 0;
        for (int i = 0; i < n; i ++) {
            if (mid > cnt[i]) sp += (mid - cnt[i]) / 2;
            else lft += (cnt[i] - mid);
        }
        return (sp >= lft);
    };

    while (hi - lo > 1) {
        int mid = (lo + hi) >> 1;
        if (chk (mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}