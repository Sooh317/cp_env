class LCA{
    using Graph = std::vector<std::vector<int>>;

private:
    std::vector<std::vector<int>> parent;
    int LOG;
    //vector<int> dep; // depth from the root
    void init(const Graph &G, int root = 0){
        int N = G.size(), LOG = 1;
        while((1<<LOG) < N) LOG++;
        parent.resize(LOG, vector<int>(N, -1));
        dep.assign(N, -1);
        sub.assign(N, 0);
        dfs(G, root, -1);
        for(int k = 0; k < LOG - 1; k++){
            for(int v = 0; v < N; v++){
                if(parent[k][v] < 0) parent[k + 1][v] = -1;
                else parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    int dfs(const Graph &G, int v, int p, int d = 0){
        parent[0][v] = p;
        dep[v] = d;
        sub[v] = 1;
        for(int nv : G[v]){
            if(nv == p) continue;
            sub[v] += dfs(G, nv, v, d + 1);
        }
        return sub[v];
    }  
 
public:
    std::vector<int> dep; // depth from the root
    std::vector<int> sub;
    
    LCA(const Graph &G, int root = 0){ init(G, root);}

    // Lowest Common Ancestor of u and v
    int query(int u, int v){
        if(dep[u] > dep[v]) swap(u, v);
        int K = parent.size();
        for(int k = 0; k < K; k++){
            if((dep[v] - dep[u]) >> k & 1) v = parent[k][v];
        }
        if(u == v) return u;
        for(int k = K - 1; k >= 0; k--){
            if(parent[k][u] != parent[k][v]){ 
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    int level_ancestor(int v, int k) {
        assert(k <= dep[v]);
        for(int i = LOG - 1; i >= 0; i--){
            if(k >> i & 1) v = parent[i][v];
        }
        return v;
    }
};