#include<vector>
#include<algorithm>
#include<iterator>
#include<queue>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

template<typename FLOWTYPE, typename COSTTYPE> class PrimalDual{ // 最小費用流 正辺のみ O(FElogV)
    public:
    FlowGraph<FLOWTYPE,COSTTYPE> G;
    std::vector<COSTTYPE> pot, dist;
    std::vector<ll> prevv, preve;
    COSTTYPE res = 0;
    FLOWTYPE fl;
    PrimalDual(FlowGraph<FLOWTYPE,COSTTYPE> G) : G(G), pot(G.v,0), dist(G.v,-1), prevv(G.v, 0), preve(G.v, 0){}

    COSTTYPE MinCostFlow(ll s, ll t, FLOWTYPE f){ // 流せないときは-1
        fl = f;
        while(fl > 0){
            std::priority_queue<std::pair<COSTTYPE, ll>, std::vector<std::pair<COSTTYPE,ll>>, std::greater<std::pair<COSTTYPE,ll>>> que;
            dist.assign(G.v,-1);
            dist[s] = 0;
            que.push(std::make_pair(0,s));
            while(!que.empty()){ //dijkstra
                std::pair<COSTTYPE,ll> p = que.top(); que.pop();
                ll v = p.second;
                if(dist[v] < p.first)continue;
                for(ll i=0; i<G.list[v].size(); i++){
                    ll eid = G.list[v][i];
                    auto e = G.edges[eid];
                    if(e.from==v && e.cap > 0 && (dist[e.to]<0 || dist[e.to]>dist[v]+e.cost+pot[v]-pot[e.to])){
                        dist[e.to] = dist[v] + e.cost + pot[v] - pot[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        que.push(std::make_pair(dist[e.to], e.to));
                    }
                }
            }
            if(dist[t]<0) return -1;
            for(ll v=0; v<G.v; v++) pot[v] += dist[v];
            FLOWTYPE d = fl;
            for(ll v=t; v!=s; v=prevv[v]) d = std::min(d, G.edges[G.list[prevv[v]][preve[v]]].cap);
            fl -= d;
            res += pot[t] * d;
            for(ll v=t; v!=s; v=prevv[v]){
                ll eid = G.list[prevv[v]][preve[v]];
                ll reid = G.list[G.edges[eid].to][G.edges[eid].tp];
                G.edges[eid].cap -= d;
                G.edges[reid].cap += d;
            }
        }
        return res;
    }
};