/**
 * Prepare G (= directed acyclic graph)
 * store the number of directed paths in the indegree array
 * V is the number of vertices
 **/

vector<int> topological_sort(vector<vector<int>> &G, vector<int> &indegree){
    int V = G.size();
    vector<int> ret;
    queue<int> que;
    for(int i = 0; i < V; i++){
        if(indegree[i] == 0) que.push(i);
    }
    while(!que.empty()){
        int v = que.front(); que.pop();
        for(int nv : G[v]){
            indegree[nv]--;
            if(indegree[nv] == 0) que.push(nv);
        }
        ret.push_back(v);
    }
    return ret;
}

vector<int> sorted;
vector<bool> done(n), now(n);
auto dfs = [&](auto self, int v)->void{
    now[v] = true;
    for(int nv : G[v]){
        if(now[nv]){
            /* cyclic */
        }
        if(done[nv]) continue;
        self(self, nv);
    }
    done[v] = true;
    now[v] = false;
    sorted.push_back(v);
};
for(int i = 0; i < n; i++) if(!done[i]) dfs(dfs, i);
reverse(sorted.begin(), sorted.end());