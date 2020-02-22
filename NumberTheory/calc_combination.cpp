#include<stdio.h>
 
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

//#########################################################
#define MAX 100
const long long mod = 1000000007;
long long fac[MAX], finv[MAX], inv[MAX];

void Com_init(){ //##O(MAX)##
    fac[0] = fac[1] = 1; // x!
    finv[0] = finv[1] = 1; // (x!)^-1
    inv[1] = 1; //x^-1
    for(int i=2;i<MAX;i++){
        fac[i] = (fac[i-1] * i) % mod;
        inv[i] = mod - inv[mod%i] * (mod/i) % mod;
        finv[i] = finv[i-1] * inv[i] % mod;
    }
}
long long Combination(int n, int k){ //calc nCk, max=n, ##O(1)##
    if(n<k || (n<0||k<0))return 0;
    return fac[n] * (finv[k] * finv[n-k] % mod) % mod;
}
long long Combination(int n, int k){ //calc nCk, max=k, ##O(k)##
    if(n<k || (n<0||k<0))return 0;
    ll ans = 1;
    for(ll i=1; i<=k; i++){
        ans *= i+n-k;
        ans %= mod;
        ans *= inv[i];
        ans %= mod;
    }
    return ans%mod;
}
//########################################################

int main(){
    Com_init();
    printf("%lld\n",Combination(12,2));
}