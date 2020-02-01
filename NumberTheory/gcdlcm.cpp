typedef long long ll;

ll gcd(ll p, ll q){
    if(p < q)std::swap(p,q);
    if(p % q == 0) return q;
    else return gcd(q, p%q);
}

ll lcm(ll p, ll q){
    return p*q/gcd(p,q);
}