/**
 * Minimum spanning tree
 * You can use this if the form of input is an adjacency matrix
 * init1 : O(|V^2|)
 * init2 : O(|E|log|V|)
 * the answer can be called by hoge.sum
 **/
struct Prim{
    int sum;
    int V;
    vector<int> mincost;
    vector<bool> used;
    Prim(vector<vector<int>> &G, int idx = 1) : sum(0){
        if(idx == 1) init1(G);
        else init2(G);
    }
    void init1(vector<vector<int>> &G){
        V = (int)G.size();
        // if i-th vertex is still not used, the i-th mincost element represents the cost to reach it from the current tree.
        mincost.assign(V, inf);
        used.assign(V, false);
        mincost[0] = 0;
        while(true){
            int nv = -1;
            for(int u = 0; u < V; u++){
                if(!used[u] && (nv == -1 || mincost[u] < mincost[nv])) nv = u;
            }
            if(nv == -1) break;
            used[nv] = true;
            sum += mincost[nv];
            for(int u = 0; u < V; u++){
                if(G[nv][u] != -1) mincost[u] = min(mincost[u], G[nv][u]); 
            }
        }
    }
    void init2(vector<vector<int>> &G){
        V = (int)G.size();
        using P = pair<ll, int>;
        priority_queue<P, vector<P>, greater<P>> que;
        used.assign(V, false);
        que.emplace(0, 0);
        while(que.size()){
            P p = que.top(); que.pop();
            int v = p.second;
            if(used[v]) continue;
            used[v] = true;
            sum += p.first;
            for(int u = 0; u < V; u++){
                if(!used[u]) que.emplace(G[v][u], u);
            }
        }
    }
};