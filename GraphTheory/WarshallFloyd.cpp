#include<stdio.h>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<queue>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

std::vector<std::vector<ll>> WarshallFloyd(Graph G, ll inf){
    std::vector<std::vector<ll>> matrix;
    matrix.assign(G.v, std::vector<ll>(G.v, inf));
    for(ll i=0; i<G.v; i++)matrix[i][i]=0;     // 負閉路が存在する場合matrix[i][i]が0でなくなる
    for(auto i : G.edges){ matrix[i.from][i.to] = i.cost; }
    for(ll k=0; k<G.v; k++)for(ll i=0; i<G.v; i++)for(ll j=0; j<G.v; j++){
        if(matrix[i][k]==inf || matrix[k][j]==inf) continue;
        matrix[i][j] = std::min(matrix[i][j], matrix[i][k]+matrix[k][j]);
    }
    return matrix;
}