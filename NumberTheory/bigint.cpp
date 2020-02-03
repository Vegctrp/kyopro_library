#include<stdio.h>
#include<vector>
#include<string>
#include<iomanip>
#include<sstream>
#include<cassert>

using namespace std;
typedef long long ll;

class bigint{
    public:
    using ll = long long;
    ll base = 100000000;
    ll base_digits = 8;
    std::vector<ll> num;
    int sign;
    int length;

    bigint() : sign(1), length(0){ num.clear(); }
    bigint(ll v) : sign(1), length(1){
        num.clear();
        if(v==0){
            length=0;
            return;
        }
        if(v<0){sign=-1; v=-v;}
        num.push_back(v);
        carryup_all();
    }
    bigint(const string s) : sign(1){
        string t = s;
        num.clear();
        if(t[0]=='-'){
            t = t.substr(1);
            sign *= -1;
        }
        int len = t.length();
        length = len / base_digits + (len % base_digits != 0);
        while(len > base_digits){
            num.push_back(std::stol(t.substr(len-base_digits, base_digits)));
            len -= base_digits;
        }
        num.push_back(std::stol(t.substr(0, len)));
        carryup_all();
    }

    void carryup(ll a){
        if(num[a] >= base){
            if(num.size() <= a+1){
                num.push_back(num[a] / base);
                length++;
            }
            else{
                num[a+1] += (num[a] / base);
            }
            num[a] %= base;
            carryup(a+1);
        }
    }
    void carryup_all(){
        ll c = 0;
        while(c < num.size())carryup(c++);
    }
    void carrydown(ll a){
        if(num[a] < 0){
            if(num.size() <= a+1) { num[a]*=-1; sign*=-1; }
            else{
                while(num[a]<0){
                    num[a+1]--;
                    num[a]+=base;
                }
                carrydown(a+1);
            }
        }
        trimming();
    }
    void carrydown_all(){
        ll c = 0;
        while(c < num.size()) carrydown(c++);
    }
    void trimming(){
        while(length!=0 && !num.back()) { num.pop_back(); length--; }
        if(num.empty()) sign = 1;
    }

    std::string to_string(){
        std::string ans;
        if(length==0){
            ans += '0';
            return ans;
        }
        if(sign==-1)ans += '-';
        std::ios::fmtflags curret_flag = std::cout.flags();
        for(int i=length-1; i>=0; i--){
            std::ostringstream ss;
            if(i==length-1)ss << num[i];
            else ss << std::setw(base_digits) << std::setfill('0') << num[i];
            ans += ss.str();
        }
        std::cout.flags(curret_flag);
        return ans;
    }

    bigint convert_base(ll to){
        std::string str = (*this).to_string();
        base_digits = to;
        base = 1;
        while(to--)base*=10;
        *this = str;
        return *this;
    }

    // =
    void operator=(ll v){
        sign = 1;
        length = 1;
        if(v<0) { sign*=-1; v*=-1; }
        num.clear();
        num.push_back(v);
        carryup(0);
    }
    void operator=(bigint v){
        if(base_digits != v.base_digits) v.convert_base(base_digits);
        sign = v.sign;
        num = v.num;
        length = v.length;
    }
    void operator=(std::string str){
        sign = 1;
        string t = str;
        num.clear();
        if(t[0]=='-'){
            t = t.substr(1);
            sign *= -1;
        }
        int len = t.length();
        length = len / base_digits + (len % base_digits != 0);
        while(len > base_digits){
            num.push_back(std::stol(t.substr(len-base_digits, base_digits)));
            len -= base_digits;
        }
        num.push_back(std::stol(t.substr(0, len)));
        carryup_all();
    }

    // +
    bigint operator+(bigint v){
        ll bv = v.base_digits;
        v.convert_base(base_digits);
        bigint ans;
        ans.base = (*this).base;
        ans.base_digits = (*this).base_digits;
        ans.length = std::max(length, v.length);
        if(sign==-1 && v.sign==1) return (v - (-*this));
        if(sign==-1 && v.sign==-1) return -((-*this) + (-v));
        if(sign==1 && v.sign==-1) return (*this - (-v));
        while(num.size() > v.num.size()) v.num.push_back(0);
        while(num.size() < v.num.size()) num.push_back(0);
        for(ll i=0; i<ans.length; i++){
            if(ans.num.size() == i) ans.num.push_back(num[i] + v.num[i]);
            else if(ans.num.size() > i) ans.num[i] = num[i] + v.num[i];
            else cout << "+ error" << endl;
        }
        ans.carryup_all();
        v.convert_base(bv);
        return ans;
    }
    bigint operator+(ll v){
        bigint v2(v);
        return *this + v2;
    }

    // -
    bigint operator-(){
        bigint ans = *this;
        ans.sign = -sign;
        return ans;
    }
    bigint operator-(bigint v){
        ll vb = v.base_digits;
        v.convert_base(base_digits);
        bigint ans;
        ans.base = (*this).base;
        ans.base_digits = (*this).base_digits;
        int len = std::max(length, v.length);
        if(sign==-1 && v.sign==1) return -((-*this) + v);
        if(sign==-1 && v.sign==-1) return -((-*this) - (-v));
        if(sign==1 && v.sign==-1) return ((-v) + *this);
        while(num.size() > v.num.size()) v.num.push_back(0);
        while(num.size() < v.num.size()) num.push_back(0);
        int lastflag=0;
        int l=0;
        for(ll i=0; i<len; i++){
            int h = num[i] - v.num[i];
            if(h>0)lastflag=1;
            else if(h<0)lastflag=-1;
            if(h!=0)l=i;
        }
        ans.sign=lastflag;
        ans.length = l+1;
        for(ll i=0; i<ans.length; i++){
            if(ans.num.size() == i) ans.num.push_back((num[i] - v.num[i])*lastflag);
            else if(ans.num.size() > i) ans.num[i] = (num[i] - v.num[i])*lastflag;
            else cout << "- error" << endl;
            
        }
        ans.carrydown_all();
        ans.carryup_all();
        v.convert_base(vb);
        return ans;
    }
    bigint operator-(ll v){
        bigint v2(v);
        return *this - v2;
    }

    // *
    std::vector<ll> karatsubaMultiply(std::vector<ll> a, std::vector<ll> b){
        // a,bの長さは同じで、2^n base_digitsは4くらい
        ll n = a.size();
        std::vector<ll> ans(n*2);
        if(n <= 32){
            for(ll i=0; i<n; i++)for(ll j=0; j<n; j++) ans[i+j] += a[i] * b[j];
            return ans;
        }
        ll k = n>>1;
        std::vector<ll> a1(a.begin(), a.begin()+k);
        std::vector<ll> a2(a.begin()+k, a.end());
        std::vector<ll> b1(b.begin(), b.begin()+k);
        std::vector<ll> b2(b.begin()+k, b.end());

        std::vector<ll> a1b1 = karatsubaMultiply(a1, b1);
        std::vector<ll> a2b2 = karatsubaMultiply(a2, b2);
        
        for(ll i=0; i<k; i++) a2[i] += a1[i];
        for(ll i=0; i<k; i++) b2[i] += b1[i];

        std::vector<ll> r=karatsubaMultiply(a2,b2);
        for(ll i=0; i<(ll)a1b1.size(); i++) r[i] -= a1b1[i];
        for(ll i=0; i<(ll)a2b2.size(); i++) r[i] -= a2b2[i];

        for(ll i=0; i<(ll)r.size(); i++) ans[i+k] += r[i];
        for(ll i=0; i<(ll)a1b1.size(); i++) ans[i] += a1b1[i];
        for(ll i=0; i<(ll)a2b2.size(); i++) ans[i+n] += a2b2[i];
        return ans;
    }
    bigint operator*(bigint v){
        ll bthis = (*this).base_digits;
        ll bv = v.base_digits;
        std::vector<ll> a = (*this).convert_base(4).num;
        std::vector<ll> b = v.convert_base(4).num;
        while(a.size() < b.size()) a.push_back(0);
        while(a.size() > b.size()) b.push_back(0);
        while(a.size() & (a.size()-1)) {a.push_back(0); b.push_back(0);}
        std::vector<ll> c = karatsubaMultiply(a,b);
        bigint ans;
        ans.convert_base(4);
        ans.num = c;
        ans.sign = sign * v.sign;
        ans.length = c.size();
        ans.carryup_all();
        ans.convert_base(8);
        ans.trimming();
        convert_base(bthis); v.convert_base(bv);
        ans.convert_base(bthis);
        return ans;
    }
    bigint operator*(ll v){
        bigint v2(v);
        return (*this)*v2;
    }

    // /,%
    std::pair<bigint, bigint> divmod(bigint a, bigint b){
        ll va = a.base_digits; a.convert_base(4);
        ll vb = b.base_digits; b.convert_base(4);
        ll norm = b.base / (b.num.back()+1);
        bigint a2 = a*norm; a2.sign = 1;
        bigint b2 = b*norm; b2.sign = 1;
        bigint q,r;
        a2.convert_base(4); b2.convert_base(4); q.convert_base(4); r.convert_base(4);
        q.num.resize(a2.num.size());
        q.length = a2.num.size();
        for(ll i=a2.num.size()-1; i>=0; i--){
            r = r * a2.base;
            r = r + a2.num[i];
            ll s1 = r.num.size() <= b2.num.size() ? 0 : r.num[b2.num.size()];
            ll s2 = r.num.size() <= b2.num.size()-1 ? 0 : r.num[b2.num.size()-1];
            ll d = (a2.base*s1+s2)/b2.num.back();
            r = r - b2*d;
            while(r<0) { r = r+b2; d = d-1;}
            q.num[i]=d;
        }
        q.sign = a.sign*b.sign;
        r.sign = a.sign;
        q.trimming(); r.trimming();
        a.convert_base(va); b.convert_base(vb);
        q.convert_base(8); r.convert_base(8);
        if(r==0) return std::make_pair(q, 0);
        return std::make_pair(q, r/norm);
    }
    bigint operator/(bigint v){
        return divmod(*this, v).first;
    }
    bigint operator/(ll v){
        bigint v2(v);
        return divmod(*this, v2).first;
    }
    bigint operator%(bigint v){
        return divmod(*this, v).second;
    }
    bigint operator%(ll v){
        bigint v2(v);
        return divmod(*this, v2).second;
    }

    // <, >, ==
    bool operator<(bigint v){
        trimming(); v.trimming();
        if(sign != v.sign) return sign<v.sign;
        if(num.size() != v.num.size()) return num.size()*sign < v.num.size()*v.sign;
        for(ll i=num.size()-1; i>=0; i--){
            if(num[i] != v.num[i]) return num[i]*sign < v.num[i]*sign;
        }
        return false;
    }
    bool operator<(ll v){
        bigint v2(v);
        return (*this)<v2;
    }
    bool operator>(bigint v){
        return v<(*this);
    }
    bool operator>(ll v){
        bigint v2(v);
        return v2<(*this);
    }
    bool operator==(bigint v){
        return !((*this)<v) && !((*this)>v);
    }
    bool operator==(ll v){
        bigint v2(v);
        return !((*this)<v2) && !((*this)>v2);
    }
};