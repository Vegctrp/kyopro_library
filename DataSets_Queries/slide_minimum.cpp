#include<vector>
#include<deque>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class slide_minimum{
    public:
    std::vector<ll> list;
    std::vector<ll> ans;
    ll n;   // listの長さ
    ll wl;  // 枠の大きさ
    std::deque<ll> deq;

    slide_minimum(ll n, ll l, std::vector<ll> list) : n(n), wl(l){
        for(ll i=0; i<n; i++) this->list.push_back(list[i]);
    }
    std::vector<ll> get(){    // 枠内の最小値のリストを求める O(n-wl)
        for(ll i=0; i<n; i++){
            while(!deq.empty() && list[deq.back()] >= list[i]) deq.pop_back();
            deq.push_back(i);

            if(i+1 >= wl){
                ans.push_back(list[deq.front()]);
                if(deq.front()==i+1-wl)deq.pop_front();
            }
        }
        return this->ans;
    }
};