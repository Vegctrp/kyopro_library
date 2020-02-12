#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class UnionFind {
    public:
    std::vector<ll> parent;
    std::vector<ll> sizes;
    UnionFind(ll N) : parent(N), sizes(N, 1) {
        for(ll i=0; i<N; i++) parent[i]=i;
    }
    ll find(ll x){
        if(x==parent[x]) return x;
        return parent[x]=find(parent[x]);
    }
    void unite(ll x, ll y){
        ll x_class = find(x);
        ll y_class = find(y);
        if(x_class == y_class) return;
        if(sizes[x_class] < sizes[y_class])std::swap(x_class, y_class);
        parent[y_class] = x_class;
        sizes[x_class] += sizes[y_class];
        sizes[y_class] = 0;
    }
    bool same(ll x, ll y){
        return find(x)==find(y);
    }
    ll size(ll x){
        return sizes[find(x)];
    }
};

Graph Kruskal(Graph G){  // 無向グラフの最小全域木、O(|E|log|V|)
    Graph ans(G.v, false);
    UnionFind uf(G.v);
    std::vector<Graph::Edge> edges = G.edges;
    sort(edges.begin(), edges.end(), [](Graph::Edge a, Graph::Edge b){return a.cost<b.cost;} );
    for(ll i=0; i<edges.size(); i++){
        if(!uf.same(edges[i].from, edges[i].to)){
            uf.unite(edges[i].from, edges[i].to);
            ans.connect(edges[i].from, edges[i].to, edges[i].cost);
        }
    }
    return ans;
}