// reference : https://opt-cp.com/fps-implementation/
// This library requires <atcoder/modint> and <atcoder/convolution>
template<class T>
struct FormalPowerSeries : vector<T>{
    using vector<T>::vector;
    using vector<T>::operator=;
    using F = FormalPowerSeries;

    // operations in O(N)
    F operator-()const{
        F res(*this);
        for (auto &e : res) e = -e;
        return res;
    }
    F &operator*=(const T &g) {
        for (auto &e : *this) e *= g;
        return *this;
    }
    F &operator/=(const T &g) {
        assert(g != T(0));
        *this *= g.inv();
        return *this;
    }
    F &operator+=(const F &g) {
        int n = (*this).size(), m = g.size();
        for(int i = 0; i < min(n, m); i++) (*this)[i] += g[i];
        return *this;
    }
    F &operator-=(const F &g) {
        int n = (*this).size(), m = g.size();
        for(int i = 0; i < min(n, m); i++) (*this)[i] -= g[i];
        return *this;
    }
    // f -> f*z^d
    F &operator<<=(const int d) {
        int n = (*this).size();
        (*this).insert((*this).begin(), d, 0);
        (*this).resize(n);
    return *this;
    }
    // f -> f*z^(-d)
    F &operator>>=(const int d) {
        int n = (*this).size();
        (*this).erase((*this).begin(), (*this).begin() + min(n, d));
        (*this).resize(n);
        return *this;
    }
    
    // return 1/f, deg(1/f) = d - 1
    // using atcoder::convolution
    F inv(int d = -1) const {
        int n = (*this).size();
        assert(n != 0 && (*this)[0] != 0);
        if (d == -1) d = n;
        assert(d > 0);
        F res{(*this)[0].inv()};
        while (res.size() < d){
            int m = size(res);
            F f(begin(*this), begin(*this) + min(n, 2*m));
            F r(res);
            f.resize(2*m), internal::butterfly(f);
            r.resize(2*m), internal::butterfly(r);
            for(int i = 0; i < 2*m; i++) f[i] *= r[i];
            internal::butterfly_inv(f);
            f.erase(f.begin(), f.begin() + m);
            f.resize(2*m), internal::butterfly(f);
            for(int i = 0; i < 2*m; i++) f[i] *= r[i];
            internal::butterfly_inv(f);
            T iz = T(2*m).inv(); iz *= -iz;
            for(int i = 0; i < m; i++) f[i] *= iz;
            res.insert(res.end(), f.begin(), f.begin() + m);
        }
        return {res.begin(), res.begin() + d};
    }

// computation for f*g & f/g, use either one of them

    //// fast: FMT-friendly modulus only -> O((N + M)log(N + M))
    /*  F &operator*=(const F &g) {
            int n = (*this).size();
            *this = convolution(*this, g);
            (*this).resize(n);
            return *this;
        }
        F &operator/=(const F &g) {
            int n = (*this).size();
            *this = convolution(*this, g.inv(n));
            (*this).resize(n);
            return *this;
        }
    */

    //// naive -> O(NM)
    /*  F &operator*=(const F &g) {
            int n = (*this).size(), m = g.size();
            for(int i = n - 1; i >= 0; i--) {
                (*this)[i] *= g[0];
                for(int j = 1; j < min(i+1, m); j++) (*this)[i] += (*this)[i-j] * g[j];
            }
            return *this;
        }
        F &operator/=(const F &g) {
            assert(g[0] != T(0));
            T ig0 = g[0].inv();
            int n = (*this).size(), m = g.size();
            for(int i = 0; i < n; i++) {
                for(int j = 1; j < min(i+1, m); j++) (*this)[i] -= (*this)[i-j] * g[j];
                (*this)[i] *= ig0;
            }
            return *this;
        }
    */

    // sparse(the coefficiets in g have K non-0s) O(NK)
    // give the pair of (degree, coefficient) in this function
    // f -> f*g
    F &operator*=(vector<pair<int, T>> g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        if (d == 0) g.erase(g.begin());
        else c = 0;
        for(int i = n - 1; i >= 0; i--){
            (*this)[i] *= c;
            for (auto &[j, b] : g) {
                if (j > i) break;
                (*this)[i] += (*this)[i-j] * b;
            }
        }
        return *this;
    }
    // f -> f/g
    F &operator/=(vector<pair<int, T>> g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        assert(d == 0 && c != T(0));
        T ic = c.inv();
        g.erase(g.begin());
        for(int i = 0; i < n; i++) {
            for (auto &[j, b] : g) {
                if (j > i) break;
                (*this)[i] -= (*this)[i-j] * b;
            }
            (*this)[i] *= ic;
        }
        return *this;
    }

    // f -> f*(1 + c*z^d) in O(N)
    void multiply(const int d, const T c) { 
        int n = (*this).size();
        if (c == T(1)) for(int i = n-d-1; i >= 0; i--) (*this)[i+d] += (*this)[i];
        else if (c == T(-1)) for(int i = n-d-1; i >= 0; i--) (*this)[i+d] -= (*this)[i];
        else for(int i = n-d-1; i >= 0; i--) (*this)[i+d] += (*this)[i] * c;
    }

    // f -> f/(1 + c*z^d) in O(N)
    void divide(const int d, const T c) {
        int n = (*this).size();
        if (c == T(1)) for(int i = 0; i < n-d; i++) (*this)[i+d] -= (*this)[i];
        else if (c == T(-1)) for(int i = 0; i < n-d; i++) (*this)[i+d] += (*this)[i];
        else for(int i = 0; i < n-d; i++) (*this)[i+d] -= (*this)[i] * c;
    }

    // return f(a)
    T eval(const T &a) const {
        T x(1), res(0);
        for (auto e : *this) res += e * x, x *= a;
        return res;
    }

    F operator*(const T &g)const{return F(*this) *= g;}
    F operator/(const T &g)const{return F(*this) /= g;}
    F operator+(const F &g)const{return F(*this) += g;}
    F operator-(const F &g)const{return F(*this) -= g;}
    F operator<<(const int d)const{return F(*this) <<= d;}
    F operator>>(const int d)const{return F(*this) >>= d;}
    F operator*(const F &g)const{return F(*this) *= g;}
    F operator/(const F &g)const{return F(*this) /= g;}
    F operator*(vector<pair<int, T>> g)const{ return F(*this) *= g;}
    F operator/(vector<pair<int, T>> g)const{ return F(*this) /= g;}
};  
using fps = FormalPowerSeries<mint>;
using sfps = vector<pair<int, mint>>;

