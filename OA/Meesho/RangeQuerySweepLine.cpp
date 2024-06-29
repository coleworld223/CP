vector <int> solve(vector <vector <int>> d, vector <int> q) {
    int n = d.size();
    int nq = q.size();
    map <int, int> cmp;
    for (int i = 0; i < n; i++) {
        cmp[d[i][0]] = 0;
        cmp[d[i][0] + d[i][1] + 1] = 0;
    }

    for (int i = 0; i < nq; i++) {
        cmp[q[i]] = 0;
    }

    int _ = 0;
    for (auto [x, y] : cmp){
        cmp[x] = _++;
    }

    // -2 -> ins, -1 -> rem, else -> qry

    vector <vector <int>> ev (_);

    for (int i = 0; i < n; i++) {
        ev[cmp[d[i][0]]].push_back(-2);
        ev[cmp[d[i][0] + d[i][1] + 1]].push_back(-1);
    }

    for (int i = 0; i < nq; i++) {
        ev[cmp[q[i]]].push_back(i);
    }

    vector <int> res (nq);

    for (int i = 0, c = 0; i < _; i++) {
        for (int x : ev[i]) {
            if (x == -2) c++;
            else if (x ==  -1) c--;
        }
        for (int x : ev[i]) if (x >= 0) {
            res[x] = c;
        }
    }
    return res;
}