#include<stdio.h>
#include<vector>
#include<iterator>
#include<queue>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

std::vector<ll> Dijkstra(Graph G, ll start, ll inf){ // 点startから各点への最短経路長 O(|E|log|V|)
    ll INF = inf;
    std::vector<ll> dist(G.v, INF);
    std::priority_queue<std::pair<ll,ll>, std::vector<std::pair<ll,ll>>, std::greater<std::pair<ll,ll>>> que;
    dist[start] = 0;
    que.push(std::make_pair(0, start));

    while(!que.empty()){
        std::pair<ll,ll> p = que.top();
        que.pop();
        if(dist[p.second] < p.first) continue;
        for(auto i : G.list[p.second]){
            if(dist[i.first] > dist[p.second] + i.second){
                dist[i.first] = dist[p.second] + i.second;
                que.push(std::make_pair(dist[i.first], i.first));
            }
        }
    }
    return dist;
}