template<class T>
class SlopeTrick{
private:
    const T INF = numeric_limits<T>::max() >> 1;
    priority_queue<T> L;
    priority_queue<T, vector<T>, std::greater<T>> R;
    T minf;
    T addl, addr;

    void push_R(const T &a){ R.push(a - addr);}
    void push_L(const T &a){L.push(a - addl);}
    T top_R() const{
        if(R.empty()) return INF;
        return R.top() + addr;
    }
    T pop_R(){
        T ret = top_R();
        if(!R.empty()) R.pop();
        return ret;
    }
    T top_L() const{
        if(L.empty()) return -INF;
        return L.top() + addl;
    }
    T pop_L(){
        T ret = top_L();
        if(!L.empty()) L.pop();
        return ret;
    }
    int size(){return (int)(L.size() + R.size());}

public:
    SlopeTrick():minf(0), addl(0), addr(0){}
    T get_min(){return minf;}
    std::pair<T, T> get_range(){return std::pair<T, T>{top_L(), top_R()};}
    void add_const(const T &a){ minf += a;}
    // add _/ (max(0, x - a))
    void add_right(const T &a){
        minf += max(T(0), top_L() - a);
        push_L(a);
        push_R(pop_L());
    }
    // add \_ (max(0, a - x))
    void add_left(const T &a){
        minf += max(T(0), a - top_R());
        push_R(a);
        push_L(pop_R());
    }
    // add \/ (|x - a|)
    void add_abs(const T &a){
        add_left(a);
        add_right(a);
    }
    // \/ -> \_
    void init_right(){ while(!R.empty()) R.pop();}
    // \/ -> _/
    void init_left(){ while(!L.empty()) L.pop(); }
    // f(x) <- \min_{y \in [x - b, x - a]} f(x)
    void shift(const T &a, const T &b){
        assert(a <= b);
        addl += a;
        addr += b;
    }
    // f(x) <- f(x - a)
    void shift(const T &a){ shift(a, a);}
    // return f(x), destroy L and R
    T get(const T &x){
        T ret = minf;
        while(!L.empty()) ret += max(T(0), pop_L() - x);
        while(!R.empty()) ret += max(T(0), x - pop_R());
        return ret;
    }
    // f(x) <- f(x) + g(x)
    void merge(SlopeTrick &st){
        if(size() < st.size()){
            swap(st.L, L);
            swap(st.R, R);
            swap(st.addl, addl);
            swap(st.addr, addr);
            swap(st.minf, minf);
        }
        while(!st.R.empty()) add_right(st.pop_R());
        while(!st.L.empty()) add_right(st.pop_L());
        minf += st.minf;
    }
};