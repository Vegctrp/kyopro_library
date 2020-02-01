#include<map>

using namespace std;
typedef long long ll;

std::map<ll, ll> PrimeFactor(ll n){
    std::map<ll, ll> answer;
    for(ll i=2;i*i<=n;i++){
        while(n%i==0){
            answer[i]++;
            n /= i;
        }
    }
    if(n!=1)answer[n]=1;
    return answer;
}