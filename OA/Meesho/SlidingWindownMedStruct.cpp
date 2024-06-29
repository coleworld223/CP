struct ds {
    multiset <int> f, l;
    void insert(int x) {
        int sf = f.size(), sl = l.size();
        if (sf <= sl) f.insert(x);
        else l.insert(x);
        while(!l.empty()) {
            int x = *f.rbegin();
            int y = *l.begin();
            if (x > y) {
                f.erase(--f.end());
                l.erase(l.begin());
                f.insert(y);
                l.insert(x);
            }
            else break;
        }
    }
    void pr() {
        for (int x : f) {
            cout << x << ' ';
        }
        cout << '\n';
        for (int x : l) {
            cout << x << ' ';
        }
        cout << '\n';
    }
    int med() {
        return *f.rbegin();
    }
};