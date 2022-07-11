#pragma region BIT
// 0-indexed
template<class T> struct BIT{
private:
    int _n, cnt;
    vector<T> data;
public:
    BIT(int n) : _n(n + 1), data(n + 1) {
        cnt = 1;
        while(cnt < n) cnt *= 2;
    };
    void add(int p, T x = 1){
        assert(0 <= p && p < _n);
        p++;
        for(;p < _n; p += p & -p) data[p] += x;
    }
    //[l, r)
    T sum(int l, int r){
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }
    //[0, r)
    T sum(int r){
        T sum = 0;
        for(; r > 0; r -= r & -r) sum += data[r];
        return sum;
    }
    //V0 + V1 + ... + Vpos >= val の posを返す
    int lower_bound(T val){
        if(val <= 0) return 0;
        int pos = 0;
        for(int k = cnt; k > 0; k >>= 1){
            int npos = pos + k;
            if(npos < _n && data[npos] < val){
                val -= data[npos];
                pos = npos;
            }
        }
        return pos;
    }
};
#pragma endregion

#pragma region TWO_D_BIT
template<class T> struct BIT{
private:
    int _n1, _n2, cnt;
    vector<vector<T>> data2;
public:
    BIT(int n1, int n2) : _n1(n1), _n2(n2) {
        data2.resize(_n1);
        for(int i = 0; i < n1; i++) data2[i].resize(_n2, 0);
    };
    void add(int x, int y, T val){
        assert(0 <= x && x < _n1 && 0 <= y && y < _n2);
        x++, y++;
        for(int i = x; i <= _n1; i++){
            for(int j = y; j <= _n2; j++){
                data2[x - 1][y - 1] += val;
            }
        }
    }
    //[0, x][0, y]
    T sum(int x, int y){
        assert(0 <= x && x < _n1 && 0 <= y && y < _n2);
        T sum = 0;
        x++, y++;
        for(int i = x; i >= 0; i -= i & -i){
            for(int j = y; j >= 0; j -= j & -j){
                sum += data2[i][j];
            }
        }
        return sum;
    }
};
#pragma endregion

#pragma region RangeAddBIT
// 0-indexed
template<class T> struct RangeAddBIT{
private:
    vector<T> a, b;
    int n;
public:
    RangeAddBIT(int _n):n(_n + 2), a(_n + 2), b(_n + 2){}
    //[l, r)
    void add(int l, int r, T x = T(1)){
        ++l, ++r;
        for(int i = l; i < n; i += i & -i) a[i] -= x * l;
		for(int i = r; i < n; i += i & -i) a[i] += x * r;
		for(int i = l; i < n; i += i & -i) b[i] += x;
		for(int i = r; i < n; i += i & -i) b[i] -= x;
    }
    // [0, r)
    T sum(int r) {
		++r;
		T ret = 0;
		for(int x = r; x > 0; x -= x & -x) ret += a[x];
		for(int x = r; x > 0; x -= x & -x) ret += b[x] * r;
		return ret;
	}
    //[l, r)
    T sum(int l, int r){return sum(r) - sum(l);}
};
#pragma endregion