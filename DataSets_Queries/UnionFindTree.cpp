#include<stdio.h>
#include<vector>

typedef long long ll;

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
        if(sizes[x_class] < sizes[y_class])std::swap(x,y);
        parent[y_class] = x_class;
        sizes[x_class] = sizes[y_class];
        sizes[y_class] = 0;
    }
    bool same(ll x, ll y){
        return find(x)==find(y);
    }
    ll size(ll x){
        return sizes[find(x)];
    }
};