#include<vector>
#include<queue>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class HopcroftKarp{ // 最大二部マッチング O(|E| sqrt(|V|))
    public:
    Graph G;  // 0-(setx-1) , setx-(setx+sety-1)が二部グラフの各頂点集合になっている前提
    ll setx, sety;
    std::vector<ll> dist, match;
    std::vector<bool> visited, vv;

    HopcroftKarp(Graph G, ll x) : G(G), setx(x),sety(G.v-setx), dist(setx,-1), match(sety,-1), visited(setx, false){}

    void bfs(){
        dist.assign(setx, -1);
        std::queue<ll> que;
        for(ll i=0; i<setx; i++)if(!visited[i]){
            que.push(i);
            dist[i]=0;
        }
        while(!que.empty()){
            ll a = que.front(); que.pop();
            for(ll i=0; i<G.list[a].size(); i++){
                ll c = match[G.list[a][i].first - setx];
                if(c>=0 && dist[c]==-1){
                    dist[c] = dist[a] + 1;
                    que.push(c);
                }
            }
        }
    }
    bool dfs(ll a){
        vv[a] = true;
        for(ll i=0; i<G.list[a].size(); i++){
            ll c = match[G.list[a][i].first - setx];
            if(c<0 || (!vv[c] && dist[c]==dist[a]+1 && dfs(c))){
                match[G.list[a][i].first - setx] = a;
                visited[a] = true;
                return true;
            }
        }
        return false;
    }
    ll Bipartite_Matching(){
        ll ret = 0;
        while(true){
            bfs();
            vv.assign(setx, false);
            ll fl = 0;
            for(ll i=0; i<setx; i++){
                if(!visited[i] && dfs(i)) fl++;
            }
            if(fl==0) return ret;
            ret += fl;
        }
    }
};
