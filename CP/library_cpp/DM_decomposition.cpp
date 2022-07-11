struct Bipartite_Matching {
    std::vector<std::vector<int>> es;
    std::vector<int> d, match;
    std::vector<bool> used, used2;
    const int n, m; // n = |Left|, m = |Right|
 
    Bipartite_Matching(int n, int m) : es(n), d(n), match(m), used(n), used2(n), n(n), m(m) {}
 
    void add_edge(int u, int v) { es[u].push_back(v); }
 
    void _bfs() {
        std::fill(d.begin(), d.end(), -1);
        queue<int> que;
        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                que.push(i);
                d[i] = 0;
            }
        }
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            for (auto &e : es[i]) {
                int j = match[e];
                if (j != -1 && d[j] == -1) {
                    que.push(j);
                    d[j] = d[i] + 1;
                }
            }
        }
    }
 
    bool _dfs(int now) {
        used2[now] = true;
        for (auto &e : es[now]) {
            int u = match[e];
            if (u == -1 || (!used2[u] && d[u] == d[now] + 1 && _dfs(u))) {
                match[e] = now, used[now] = true;
                return true;
            }
        }
        return false;
    }
 
    int bipartite_matching() {
        std::fill(match.begin(), match.end(), -1), std::fill(used.begin(), used.end(), false);
        int ret = 0;
        while (true) {
            _bfs();
            std::fill(used2.begin(), used2.end(), false);
            int flow = 0;
            for (int i = 0; i < n; i++) {
                if (!used[i] && _dfs(i)) flow++;
            }
            if (flow == 0) break;
            ret += flow;
        }
        return ret;
    }
};

// https://atcoder.jp/contests/abc223/submissions/27057493
// https://www.ieice.org/publications/conference-FIT-DVDs/FIT2008/pdf/D/D_023.pdf 
struct Dulmage_Mendelsohn_Decomposition : Bipartite_Matching {
    using BM = Bipartite_Matching;
    std::vector<std::vector<int>> rs;
    std::vector<std::vector<int>> ids_l, ids_r; // 左側と右側のブロック
    std::vector<int> comp_l, comp_r;       // 属するブロックの番号
    std::vector<int> vs;
 
    Dulmage_Mendelsohn_Decomposition(int n, int m) : BM(n, m), rs(n), comp_l(n), comp_r(n) {}
 
    void _dfs(int now, int col) {
        if (comp_l[now] != n + 1) return;
        comp_l[now] = col;
        for (auto &e : this->es[now]) {
            int to = this->match[e];
            if (to != -1) _dfs(to, col);
        }
        if (col > 0) vs.push_back(now);
    }
 
    void _rdfs(int now, int col) {
        if (comp_l[now] != n + 1) return;
        comp_l[now] = col;
        for (auto &e : rs[now]) _rdfs(e, col);
    }
 
    void decompose() {
        this->bipartite_matching();
        for (int i = 0; i < n; i++) {
            for (auto &e : this->es[i]) {
                int to = this->match[e];
                if (to != -1) rs[to].push_back(i); // マッチングがある辺はrsに入る
            }
        }
        std::fill(comp_l.begin(), comp_l.end(), n + 1);
        for (int i = 0; i < n; i++) { // rdfs は 逆辺を張ったグラフ上で探索し、V0を見つける
            bool flag = true;
            for (auto &e : es[i]) {
                if (this->match[e] == -1) {
                    _rdfs(i, 0);
                    flag = false;
                } else if (this->match[e] == i) {
                    flag = false;
                }
            }
            if (flag) _dfs(i, -1);
        }
        for (int i = 0; i < n; i++) _dfs(i, 1);
        for (int i = 0; i < n; i++) {
            if (comp_l[i] > 0) comp_l[i] = n + 1;
        }
        reverse(vs.begin(), vs.end());
        int cnt = 1;
        for (auto &e : vs) {
            if (comp_l[e] == n + 1) _rdfs(e, cnt++);
        }
        for (int i = 0; i < n; i++) {
            if (comp_l[i] == -1) comp_l[i] = cnt;
        }
        for (int i = 0; i < m; i++) {
            if (this->match[i] == -1) {
                comp_r[i] = 0;
            } else {
                comp_r[i] = comp_l[this->match[i]];
            }
        }
        ids_l.resize(cnt + 1), ids_r.resize(cnt + 1);
        for (int i = 0; i < m; i++) {
            if (this->match[i] == -1) ids_r[0].push_back(i);
        }
        std::vector<bool> used(n, false);
        for (int i = 0; i < m; i++) {
            int e = this->match[i];
            if (e != -1) {
                ids_l[comp_l[e]].push_back(e);
                ids_r[comp_r[i]].push_back(i);
                used[e] = true;
            }
        }
        for (int i = 0; i < n; i++) {
            if (!used[i]) ids_l[cnt].push_back(i);
        }
    }
};