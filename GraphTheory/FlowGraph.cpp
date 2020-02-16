#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

template<typename FLOWTYPE, typename COSTTYPE> class FlowGraph{
    public:
    typedef struct Edge{
        ll id, from, fp, to, tp;
        FLOWTYPE cap, icap;
        COSTTYPE cost;
        Edge(ll from, ll fp, ll to, ll tp, FLOWTYPE cap, COSTTYPE cost, ll id=-1)
                : id(id), from(from), fp(fp), to(to), tp(tp), cap(cap), icap(cap), cost(cost){}
    } Edge;

    bool isDirected;
    ll v;
    std::vector<Edge> edges;
    std::vector<std::vector<ll>> list;

    FlowGraph() : isDirected(false) { init(0); }
    FlowGraph(ll n, bool isDirected=false) : isDirected(isDirected) { init(n); }

    void init(ll n){
        v = n;
        edges.clear();
        list.assign(n, std::vector<ll>());
    }
    void add_edge(ll from, ll to, FLOWTYPE cap, COSTTYPE cost){
        edges.push_back(Edge(from, list[from].size(), to, list[to].size()+1, cap, cost, edges.size()));
        list[from].push_back(edges.size()-1);
        list[to].push_back(edges.size()-1);
        edges.push_back(Edge(to, list[to].size(), from, list[from].size()-1, 0, -cost, edges.size()));
        list[from].push_back(edges.size()-1);
        list[to].push_back(edges.size()-1);
    }
    void add_undirected_edge(ll from, ll to, FLOWTYPE cap, COSTTYPE cost){
        edges.push_back(Edge(from, list[from].size(), to, list[to].size()+1, cap, cost, edges.size()));
        list[from].push_back(edges.size()-1);
        list[to].push_back(edges.size()-1);
        edges.push_back(Edge(to, list[to].size(), from, list[from].size()-1, cap, cost, edges.size()));
        list[from].push_back(edges.size()-1);
        list[to].push_back(edges.size()-1);
    }
};
