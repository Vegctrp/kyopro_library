#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

// use FlowGraph
template<typename FLOWTYPE> class FordFulkerson{ // 最大流 maxO(maxflow*|E|)
    public:
    FlowGraph<FLOWTYPE,ll> G;
    std::vector<bool> visited;
    FordFulkerson(FlowGraph<ll,ll> G) : G(G){}
    FLOWTYPE dfs(ll v, ll t, FLOWTYPE fl){
        if(v==t) return fl;
        visited[v] = true;
        for(ll i=0; i<G.list[v].size(); i++){
            FlowGraph<ll,ll>::Edge e = G.edges[G.list[v][i]];
            if(!visited[e.to] && e.cap>0){  // FLOWTYPE > FLOWTYPE
                FLOWTYPE d = dfs(e.to, t, std::min(fl, e.cap));  // std::min(FLOWTYPE, FLOWTYPE)
                if(d > 0){  // FLOWTYPE > FLOWTYPE
                    G.edges[G.list[v][i]].cap -= d;   // FLOWTYPE - FLOWTYPE
                    G.edges[G.list[e.to][e.tp]].cap += d;  // FLOWTYPE + FLOWTYPE
                    return d;
                }
            }
        }
        return 0;
    }
    FLOWTYPE max_flow(ll s, ll t){
        FLOWTYPE flow = 0;
        while(true){
            visited.assign(G.v, false);
            FLOWTYPE f = dfs(s,t,1LL<<62);
            if(f==0)break;   // FLOWTYPE==0
            flow += f;  // FLOWTYPE + FLOWTYPE
        }
        return flow;
    }
};

// use Graph
class FordFulkerson{ // 最大流 maxO(maxflow*|E|)
    public:
    typedef struct El{
        ll to, cost, rev; // rev : toの隣接リストにおける辺の番号
        El(ll t, ll c, ll r): to(t),cost(c),rev(r){}
    } El;

    Graph G;
    std::vector<bool> visited;
    std::vector<std::vector<El>> flow, remain;

    FordFulkerson(Graph G) : G(G), visited(G.v, false){
        flow.assign(G.v, std::vector<El>());
        remain.assign(G.v, std::vector<El>());
        for(auto e : G.edges){
            flow[e.from].push_back(El(e.to, 0, flow[e.to].size()));
            flow[e.to].push_back(El(e.from, -1, flow[e.from].size()-1));  // 流れないはずの辺
            remain[e.from].push_back(El(e.to, e.cost, remain[e.to].size()));
            remain[e.to].push_back(El(e.from, 0, remain[e.from].size()-1));
        }
    }
    ll dfs(ll v, ll t, ll fl){
        if(v==t) return fl;
        visited[v] = true;
        for(ll i=0; i<remain[v].size(); i++){
            // edge : remain[v][i]
            if(!visited[remain[v][i].to] && remain[v][i].cost>0){
                ll d = dfs(remain[v][i].to, t, std::min(fl, remain[v][i].cost));
                if(d>0){
                    remain[v][i].cost -= d;
                    remain[remain[v][i].to][remain[v][i].rev].cost += d;
                    if(flow[v][i].cost == -1){
                        if(flow[flow[v][i].to][flow[v][i].rev].cost >= d) flow[flow[v][i].to][flow[v][i].rev].cost -= d;
                        else{ cout << "error" << endl;}
                    }
                    flow[v][i].cost += d;
                    return d;
                }
            }
        }
        return 0;
    }
    ll max_flow(ll s, ll t){
        ll flow = 0;
        while(true){
            visited.assign(G.v, false);
            ll f = dfs(s, t, 1LL<<62);
            if(f==0) break;
            flow += f;
        }
        return flow;
    }
};