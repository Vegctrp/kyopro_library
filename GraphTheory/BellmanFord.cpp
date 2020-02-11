#include<vector>
#include<iterator>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

std::vector<ll> BellmanFord(Graph G, ll start, ll inf){ // 点startから各点への最短経路長
    std::vector<ll> dist(G.v, inf);
    std::vector<bool> negative(G.v, 0);
    dist[start] = 0;

    REP(i, G.v){
        for(auto edge : G.edges){
            if(dist[edge.from]==inf)continue;
            if(dist[edge.to]>dist[edge.from]+edge.cost){
                dist[edge.to] = dist[edge.from] + edge.cost;
            }
        }
    }
    REP(i,G.v){
        for(auto edge : G.edges){
            if(dist[edge.from]==inf)continue;
            if(dist[edge.to] > dist[edge.from]+edge.cost) negative[edge.to]=true;
            if(negative[edge.from]==true)negative[edge.to]=true;
        }
    }
    std::vector<ll> ans = dist;
    REP(i,G.v)if(negative[i]==true) ans[i]=-inf;
    return ans;
}