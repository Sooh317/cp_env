// ax + by = gcd(a, b) = g となる x, y, g を返す
ll extgcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    ll g = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}