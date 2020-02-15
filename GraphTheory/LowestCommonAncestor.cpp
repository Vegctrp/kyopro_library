#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class LowestCommonAncestor{ // 根付き木の最小共通祖先(ダブリング) 構築O(VlogV) query O(logV)
    public:
    int LOG = 1;
    Graph G;
    std::vector<ll> depth;
    std::vector<std::vector<ll>> table; // table[k][v] : vから2^k回親をたどったnode

    LowestCommonAncestor(Graph G) : G(G), depth(G.v, 0){
        ll val = 1;
        while(val < G.v) {val <<= 1; LOG++;}
        table.assign(LOG, std::vector<ll>(G.v, -1));
    }
    void dfs(ll idx, ll parent, ll dep){
        table[0][idx] = parent;
        depth[idx] = dep;
        for(auto to : G.list[idx]){
            if(to.first != parent) dfs(to.first, idx, dep+1);
        }
    }
    void build(){
        dfs(0, -1, 0);
        for(ll k=0; k+1<LOG; k++){
            for(ll i=0; i<table[k].size(); i++){
                if(table[k][i] == -1) table[k+1][i] = -1;
                else table[k+1][i] = table[k][table[k][i]];
            }
        }
    }
    ll query(ll u, ll v){
        if(depth[u] > depth[v]) std::swap(u,v);
        for(ll i=LOG-1; i>=0; i--){
            if(((depth[v] - depth[u]) >> i ) & 1) v = table[i][v];
        }
        if(u==v) return u;
        for(ll i=LOG-1; i>=0; i--){
            if(table[i][u] != table[i][v]){
                u = table[i][u];
                v = table[i][v];
            }
        }
        return table[0][u];
    }
};