#include<vector>
#include<iterator>
#include<queue>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

Graph Prim(Graph G){
    Graph ans(G.v, false);
    std::vector<bool> visited(G.v, false);
    std::priority_queue<std::pair<ll,std::pair<ll,ll>>, std::vector<std::pair<ll,std::pair<ll,ll>>>, std::greater<std::pair<ll,std::pair<ll,ll>>>> que;
    que.push(std::make_pair(0, std::make_pair(0,0)));  //頂点0からスタート

    while(!que.empty()){
        std::pair<ll,std::pair<ll,ll>> p = que.top();
        ll cost = p.first;
        ll from = p.second.first;
        ll to = p.second.second;
        que.pop();
        if(visited[to])continue;
        visited[to] = true;
        if(from!=to) ans.connect(from, to, cost);
        for(auto i : G.list[to]) que.push(std::make_pair(i.second, std::make_pair(to, i.first)));
    }
    return ans;
}