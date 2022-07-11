template<typename T>
class Kitamasa{
// 0-indexed
// a[i + k] = d[i] * a[i] + ... + d[i + k - 1] * a[i + k - 1]
private:
    vector<T> a;
    vector<T> d;
    int k;
    // return the coefficient vector of a[n - 1]
    vector<T> solve(ll n){
        if(n == k) return d;
        vector<T> res(k);
        if(n & 1 || n < k * 2){
            vector<T> tmp = solve(n - 1);
            for(int i = 0; i < k; i++) res[i] = d[i] * tmp[k - 1];
            for(int i = 0; i + 1 < k; i++) res[i + 1] += tmp[i];
        }
        else{
            vector<vector<T>> tmp(k, vector<T>(k));
            tmp[0] = solve(n >> 1);
            for(int i = 0; i + 1 < k; i++){
                for(int j = 0; j < k; j++) tmp[i + 1][j] = d[j] * tmp[i][k - 1];
                for(int j = 0; j + 1 < k; j++) tmp[i + 1][j + 1] += tmp[i][j];
            }
            for(int i = 0; i < k; i++){
                for(int j = 0; j < k; j++){
                    res[j] += tmp[0][i] * tmp[i][j];
                }
            }
        }
        return res;
    }
public:
    Kitamasa(vector<T> &_a, vector<T> &_d) : a(_a), d(_d), k((int)a.size()){}
    
    // return a[n - 1]
    T calculate(ll n){
        if(n < k) return a[n];
        vector<T> x = solve(n);
        T res = 0;
        for(int i = 0; i < k; i++) res += x[i] * a[i];
        return res;
    }
};