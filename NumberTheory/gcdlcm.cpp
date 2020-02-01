#include<vector>

typedef long long ll;

ll gcd(ll p, ll q){
    if(p < q)std::swap(p,q);
    if(p % q == 0) return q;
    else return gcd(q, p%q);
}

ll lcm(ll p, ll q){
    return p*q/gcd(p,q);
}

std::vector<ll> extended_gcd(ll a, ll b){ //ax+by=zとなる(x,y,z)
    ll s=0;
    ll old_s=1;
    ll t=1;
    ll old_t=0;
    ll r=b;
    ll old_r=a;
    while(r){
        long q =old_r / r;
        std::swap(s, old_s); s-=q*old_s;
        std::swap(t, old_t); t-=q*old_t;
        std::swap(r, old_r); r-=q*old_r;
    }
    std::vector<ll> ans = {old_r, old_s, old_t};
    return ans;
}