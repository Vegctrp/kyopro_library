#include<vector>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class Graph{
    public:
    typedef struct Edge{
        ll from, to, cost;
        Edge(ll f, ll t, ll c): from(f),to(t),cost(c){}
    } Edge;

    bool isDirected;
    ll INF = 1 << 30;
    ll v; // 頂点数
    std::vector<Edge> edges;  // 辺のリスト
    std::vector<std::vector<std::pair<ll,ll>>> list;  // 隣接リスト
    //std::vector<std::vector<ll>> matrix; // 隣接行列

    Graph(ll n, bool isDirected=false) : isDirected(isDirected) { init(n); }
    void init(ll n){
        v=n;
        edges.clear();
        list.assign(n, std::vector<std::pair<ll,ll>>());
        //matrix.assign(n, std::vector<ll>(n, INF));
    }
    void connect(ll from, ll to){
        con(from, to, 1);
        if(!isDirected) con(to, from, 1);
    }
    void connect(ll from, ll to, ll cost){
        con(from, to, cost);
        if(!isDirected) con(to, from, cost);
    }
    void con(ll from, ll to, ll cost){
        edges.push_back(Edge(from,to,cost));
        list[from].push_back(std::make_pair(to, cost));
        //matrix[from][to] = cost;
    }
};