template<class T>
struct DualSegmentTree{
private:
    virtual void c(T&, const T&) = 0;
    int size = 1, rank = 0;
    vector<T> lazy;
    const T def_lazy;
    void push(int k){ //k番目のノードが正確な値になるように伝播
        if(!k) return;
        int r = 31 - __builtin_clz(k); // (k >> r) = 1
        for(int i = r; i > 0; i--){
            int p = k >> i;
            if(lazy[p] != def_lazy){
                c(lazy[p*2], lazy[p]);
                c(lazy[p*2+1], lazy[p]);
                lazy[p] = def_lazy;
            }
        }
    }
public:
    DualSegmentTree(int n, const T& def_value, const T& _def_lazy):def_lazy(_def_lazy){
        while(size < n) size <<= 1, rank++;
        lazy.assign(size*2, def_lazy);
        for(int i = size; i < size * 2; i++) lazy[i] = def_value;
    }
    DualSegmentTree(const vector<T> &v, const T& _def_lazy):def_lazy(_def_lazy){
        while(size < v.size()) size <<= 1, rank++;
        lazy.assign(size*2, def_lazy);
        for(int i = 0; i < v.size(); i++) lazy[i + size] = v[i];
    }
    T operator[](int k){
        k += size;
        push(k);
        return lazy[k];
    }
    void set(int k, const T& val){
        k += size;
        push(k);
        lazy[k] = val;
    }
    void query(int l, int r, const T& val){
        if(l >= r) return;
        l += size;
        r += size;
        push(l >> __builtin_ctz(l));
        push((r >> __builtin_ctz(r))-1);
        for(; l < r; l >>= 1, r >>= 1){
            if(l & 1) c(lazy[l++], val);
            if(r & 1) c(lazy[--r], val);
        }
    }
};
template<class T>
struct RAQ : DualSegmentTree<T>{
    using Base = DualSegmentTree<T>;
private:
    void c(T& a, const T& b){ a += b; }
public:
    RAQ(int n, const T& def_value = T(), const T& def_lazy = T()) : Base(n, def_value, def_lazy){}
    RAQ(const vector<T>& v, const T& def_lazy = T()) : Base(v, def_lazy){}
};
template<class T>
struct RUQ : DualSegmentTree<T>{
    using Base = DualSegmentTree<T>;
private:
    void c(T& a, const T& b){ a = b; }
public:
    RUQ(int n, const T& def_value, const T& def_lazy = numeric_limits<T>::max()) : Base(n, def_value, def_lazy){}
    RUQ(const vector<T>& v, const T& def_lazy = numeric_limits<T>::max()) : Base(v, def_lazy){}
};
template<class T>
struct RchmQ : DualSegmentTree<T>{
    using Base = DualSegmentTree<T>;
private:
    void c(T& a, const T& b){ chmin(a, b); }
public:
    RchmQ(int n, const T& def_value, const T& def_lazy = numeric_limits<T>::max()) : Base(n, def_value, def_lazy){}
    RchmQ(const vector<T>& v, const T& def_lazy = numeric_limits<T>::max()) : Base(v, def_lazy){}
};