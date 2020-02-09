#include<stdio.h>
#include<vector>
#include<iostream>
#include<functional>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll n,q,a;
    cin >> n >> q;

    // make list
    vector<ll> list;
    REP(i,n){
        cin >> a;
        list.push_back(a);
    }

    ll ans = 0;

    //begin syakutori
    ll l=0, r=0;
    ll stat=0;     //define status
    for(l=0; l<n; l++){
        while(r<n &&
            //stat+list[r]<=x  // rをインクリメントしたときに満たされてほしい条件
        ){
            stat += list[r];
            r++;               // 実際にインクリメント
        }
        //operate
        ans += r-l;
        //increment
        if(r==l)r++;
        else stat -= list[l];
}