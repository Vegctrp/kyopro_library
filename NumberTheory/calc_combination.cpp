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
long long Combination(int n, int k){ //calc nCk, ##O(1)##
    if(n<k || (n<0||k<0))return 0;
    return fac[n] * (finv[k] * finv[n-k] % mod) % mod;
}
//########################################################

int main(){
    Com_init();
    printf("%lld\n",Combination(12,2));
}