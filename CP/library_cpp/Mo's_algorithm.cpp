template<void(*add)(int), void(*del)(int)>
struct Mo{
private:
    vector<int> left, right, ord;
    vector<bool> v; // keep track of the range that is valid
    int wid, nl, nr, ptr;

    inline void init(int idx){
        v[idx].flip();
        if(v[idx]) add(idx);
        else del(idx);
    }
public:    
    Mo(int n) : wid((int)sqrt(n)), nl(0), nr(0), ptr(0), v(n){}

    // insert a query on [l, r)
    void insert(int l, int r){
        left.push_back(l);
        right.push_back(r);
    }
    // after insertion, before processing 
    void build(){
        ord.resize(left.size());
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b){
            if(left[a] / wid != left[b] / wid) return left[a] < left[b];
            return right[a] < right[b];
        });
    }
    // return query number
    int process(){
        if(ptr == ord.size()) return -1;
        const auto id = ord[ptr];
        while(nl > left[id]) init(--nl);
        while(nr < right[id]) init(nr++);
        while(nl < left[id]) init(nl++);
        while(nr > right[id]) init(--nr);
        return (ord[ptr++]);
    }
};