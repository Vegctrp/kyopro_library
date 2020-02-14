#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class lowlink{
    public:
    Graph G; // 無向グラフ
    std::vector<ll> used, ord, low;
    std::vector<ll> articulation; // 関節点
    std::vector<Graph::Edge> bridge; // 橋

    lowlink(Graph G) : G(G){
        used.assign(G.v, 0);
        ord.assign(G.v, 0);
        low.assign(G.v, 0);
    }

    ll dfs(ll idx, ll k, ll parent){
        used[idx] = true;
        ord[idx] = k++;
        low[idx] = ord[idx];
        bool isArticulation = false;
        int child_num = 0;
        for(auto to : G.list[idx]){
            if(!used[to.first]){
                child_num++;
                k = dfs(to.first, k, idx);
                low[idx] = std::min(low[idx], low[to.first]);
                isArticulation |= (parent != -1 && low[to.first] >= ord[idx]);
                if(ord[idx] < low[to.first]){
                    if(idx < to.first)bridge.push_back(Graph::Edge(idx, to.first, to.second));
                    else bridge.push_back(Graph::Edge(to.first, idx, to.second));
                }
            }
            else if(to.first != parent){
                low[idx] = std::min(low[idx], ord[to.first]);
            }
        }
        isArticulation |= (parent==-1 && child_num>1);
        if(isArticulation) articulation.push_back(idx);
        return k;
    }
    void build(){
        ll k=0;
        for(ll i=0; i<G.v; i++){
            if(!used[i]) k = dfs(i, k, -1);
        }
        std::sort(articulation.begin(), articulation.end());
        std::sort(bridge.begin(), bridge.end(), [](Graph::Edge a, Graph::Edge b){return (a.from==b.from) ? a.to<b.to : a.from<b.from;});
    }
};