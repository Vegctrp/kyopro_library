#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<queue>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

template<typename FLOWTYPE> class Dinic{  // 最大流 最大流 maxO(EV^2)
    public:
    FlowGraph<FLOWTYPE,ll> G;
    std::vector<ll> level, iter;
    Dinic(FlowGraph<FLOWTYPE,ll> G) : G(G){}

    void bfs(ll s){
        level.assign(G.v, -1);
        level[s] = 0;
        std::queue<ll> que; que.push(s);
        while(!que.empty()){
            ll v = que.front(); que.pop();
            for(ll i=0; i<G.list[v].size(); i++){
                FlowGraph<ll,ll>::Edge e = G.edges[G.list[v][i]];
                if(level[e.to]<0 && e.cap>0){  // FLOWTYPE > FLOWTYPE
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }
    FLOWTYPE dfs(ll v, ll t, ll fl){
        if(v==t)return fl;
        for(ll i=iter[v]; i<G.list[v].size(); i++){
            iter[v] += 1;
            FlowGraph<ll, ll>::Edge e = G.edges[G.list[v][i]];
            FlowGraph<ll, ll>::Edge re = G.edges[G.list[e.to][e.tp]];
            if(level[v] < level[e.to] && e.cap>0){  // FLOWTYPE > FLOWTYPE
                FLOWTYPE d = dfs(e.to, t, std::min(fl, e.cap)); // std::min(FLOWTYPE, FLOWTYPE)
                if(d>0){// FLOWTYPE > FLOWTYPE
                    G.edges[G.list[v][i]].cap -= d;  // FLOWTYPE - FLOWTYPE
                    G.edges[G.list[e.to][e.tp]].cap += d;  // FLOWTYPE + FLOWTYPE
                    return d;
                }
            }
        }
        return 0;
    }
    FLOWTYPE max_flow(ll s, ll t){
        level.assign(G.v, -1);
        iter.assign(G.v, 0);
        FLOWTYPE flow = 0;
        while(true){
            bfs(s);
            if(level[t] < 0) return flow;
            iter.assign(G.v, 0);
            FLOWTYPE f = dfs(s,t,1LL<<62);
            if(f>0) flow += f;  // FLOWTYPE > FLOWTYPE, FLOWTYPE + FLOWTYPE
        }
    }
};