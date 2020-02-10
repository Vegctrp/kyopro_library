#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class Rectangles { // 長方形の数nに対してO(n)
    public:
    ll n;
    std::vector<ll> xs;  // n番目の長方形の左上のx座標->n*2, 右下のx座標->n*2+1
    std::vector<ll> ys;
    std::vector<ll> xss;  // xs, ysをsortしたもの exのy,xに対応
    std::vector<ll> yss;
    std::vector<std::vector<ll>> ex;

    Rectangles(ll n) : n(n){
        xs.assign(n*2+1, 0); ys.assign(n*2+1, 0);
        ex.assign(n*2+1, std::vector<ll>(n*2+1, 0));
    }

    void push(ll num, ll x1, ll y1, ll x2, ll y2){
        xs[num*2]=x1; xs[num*2+1]=x2;
        ys[num*2]=y1; ys[num*2+1]=y2;
    }
    void build(){
        xss = xs;
        yss = ys;
        std::sort(xss.begin(), xss.end()); std::sort(yss.begin(), yss.end());
        for(ll i=0; i<n; i++){
            ll xl = std::distance(xss.begin(), std::lower_bound(xss.begin(), xss.end(), xs[i*2]));
            ll yl = std::distance(yss.begin(), std::lower_bound(yss.begin(), yss.end(), ys[i*2]));
            ll xr = std::distance(xss.begin(), std::lower_bound(xss.begin(), xss.end(), xs[i*2+1]));
            ll yr = std::distance(yss.begin(), std::lower_bound(yss.begin(), yss.end(), ys[i*2+1]));
            ex[yl][xl]++;
            ex[yl][xr]--;
            ex[yr][xl]--;
            ex[yr][xr]++;
        }
        for(ll x=0; x<=n*2; x++)for(ll y=0; y<n*2; y++) ex[y+1][x] += ex[y][x];
        for(ll y=0; y<=n*2; y++)for(ll x=0; x<n*2; x++) ex[y][x+1] += ex[y][x];
    }

    ll calc_area(){
        ll ans=0;
        for(ll x=0; x<n*2; x++)for(ll y=0; y<n*2; y++)if(ex[y][x]>0){
            ans += (xss[x+1]-xss[x]) * (yss[y+1]-yss[y]);
        }
        return ans;
    }
    ll max_overlap(){
        ll max=-1;
        for(ll xx=0; xx<n*2; xx++)for(ll yy=0; yy<=n*2; yy++)if(ex[yy][xx]>max){
            max = ex[yy][xx];
        }
        return max;
    }
};




class Rectangles {  // 矩形が入り得る領域のx,yに対してO(xy)
    public:
    ll n, x, y;  // [0,x),[0,y)
    std::vector<ll> xs;  // n番目の長方形の左上のx座標->n*2, 右下のx座標->n*2+1
    std::vector<ll> ys;
    std::vector<std::vector<ll>> ex;

    Rectangles(ll n, ll x, ll y) : n(n), x(x), y(y){
        xs.assign(n*2+1, 0); ys.assign(n*2+1, 0);
        ex.assign(y+1, std::vector<ll>(x+1, 0));
    }

    void push(ll num, ll x1, ll y1, ll x2, ll y2){
        xs[num*2]=x1; xs[num*2+1]=x2;
        ys[num*2]=y1; ys[num*2+1]=y2;
    }
    void build(){
        for(ll i=0; i<n; i++){
            ex[ys[i*2]][xs[i*2]]++;
            ex[ys[i*2+1]][xs[i*2]]--;
            ex[ys[i*2]][xs[i*2+1]]--;
            ex[ys[i*2+1]][xs[i*2+1]]++;
        }
        for(ll xx=0; xx<x; xx++)for(ll yy=0; yy<y; yy++) ex[yy+1][xx] += ex[yy][xx];
        for(ll yy=0; yy<y; yy++)for(ll xx=0; xx<x; xx++) ex[yy][xx+1] += ex[yy][xx];
    }

    ll calc_area(){
        ll ans=0;
        for(ll xx=0; xx<=x; xx++)for(ll yy=0; yy<=y; yy++)if(ex[yy][xx]>0){
            ans++;
        }
        return ans;
    }
    ll max_overlap(){
        ll max=-1;
        for(ll xx=0; xx<=x; xx++)for(ll yy=0; yy<=y; yy++)if(ex[yy][xx]>max){
            max = ex[yy][xx];
        }
        return max;
    }
};