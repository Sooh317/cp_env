// from is the departure point, to means the destination and cost is the weight of an edge
struct Edge{ll from, to, cost;};

struct Graph{
    ll num;
    vector<Edge> G;
    vector<ll> dist;
	vector<bool> negative;
    // constructor for initialization
    graph(ll n) : num(n), dist(n), negative(n){}
    // assembling a graph whose edge is coming from s to t
    void add_edge(ll s, ll t, ll cost){
        Edge e;
        e.from = s;
        e.to = t;
        e.cost = cost;
        G.push_back(e);
    }    
    // Bellman-Ford algorithm
    // O(|V||E|)
    // you can use this even when a graph contains a negative weighted path
    void Bellman_Ford(ll s){
        for(int i = 0; i < num; i++){
            dist[i] = INF;
        }
        dist[s] = 0;
        for(int i = 0; i < num - 1; i++){ // 頂点数-1 回やる
            for(int j = 0; j < G.size(); j++){
                Edge e = G[j];
				//自己ループの負辺があったら、dist[e.from] != INFを入れないとsから辿り着く前に勝手に更新されるので誤った答えになりうる
                if(dist[e.from] != INF && dist[e.to] > dist[e.from] + e.cost){
                    dist[e.to] = dist[e.from] + e.cost;
                    /*if(i == num - 1){
                        dist[num - 1] = INF;
						break;
                    }*/
                }
            }
        }
    }
	// after Bellman-Ford algorithm (we assume the shortest paths have to be determined so far)
	// find negative roops along the path from s to each vertex.
	void find_negative(){
		for(int i = 0; i < num; i++) negative[i] = false;
		for(int i = 0; i < num; i++){
			for(int j = 0; j < G.size(); j++){
				Edge e = G[j];
				//自己ループの負辺があると、sから辿り着けない頂点からの影響が生じる
				//この時点でdistがINFならsから行けない
				if(dist[e.from] != INF && dist[e.from] + e.cost < dist[e.to]){
					dist[e.to] = dist[e.from] + e.cost;
					negative[e.to] = true;
				}
				// 必ずしも負のループから更新があるとは限らないので、負ループに属するものからは更新する
				if(negative[e.from]) negative[e.to] = true;
			}
		}
	}
};
