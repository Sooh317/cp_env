// 0は常に入っている。
// wには配列Aの半分の要素を入れる
vector<ll> f(const vector<ll> &w){
    int n = w.size();
    vector<ll> res = {0};
    for(int i = 0; i < (1 << n); i++){
        ll tmp = 0;
        rep(j, n){
            if(i & (1 << j)){
                tmp += w[j];
            }
        }
        res.push_back(tmp);
    }
    sort(res.begin(), res.end());
    return res;
}

// 尺取りと合わせてO(2^N/2)の方法
// forループで各要素についてこれを呼び出す
void g(vector<ll> &v, ll a){
    int n = v.size();
    for(int i = 0; i < n; i++){
        v.push_back(v[i] + a);
    }
    inplace_merge(v.begin(), v.begin() + n, v.end());
    return;
}