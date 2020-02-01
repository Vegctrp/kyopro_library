#include<stdio.h>
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

ll EulersPhiFunction(ll n){  //n について、1 から n までの自然数のうち n と互いに素なものの個数
    ll num = n;
    auto primes = PrimeFactor(n);
    for(auto i:primes){
        num *= i.first-1;
        num /= i.first;
    }
    return num;
}