struct DSU {
    vector <int> p;
    vector <set <int>> st;
    DSU (int n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        st.resize(n);
        for (int i = 0; i < n; i += 1) {
            st[i].insert(i);
        }
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return 0;
        if (st[x].size() < st[y].size()) swap(x, y);
        p[y] = x;
        if (st[y].size() > st[x].size()) swap (st[y], st[x]);
        for (int ele : st[y]) {
            st[x].insert(ele);
        }
        st[y].clear();
        return 1;
    }
};

vector <int> solve (int n, vector <vector <int>> c, vector <vector <int>> q) {
    DSU d(n);

    for (int i = 0; i < c.size(); i += 1) {
        int x = --c[i][0], y = --c[i][1];
        d.merge(x, y);
    }

    vector <int> res;

    for (int i = 0; i < q.size(); i += 1) {
        if (q[i][0] == 1) {
            int x = q[i][1];
            x--;
            int p = d.find(x);
            if (d.st[p].count(x)) res.push_back(x + 1);
            else if (d.st[p].empty()) res.push_back(-1);
            else res.push_back((*d.st[p].begin()) + 1);
        }
        else {
            int x = q[i][1];
            x--;
            int p = d.find(x);
            if (d.st[p].count(x)) d.st[p].erase(x);
        }
    }

    return res;
}