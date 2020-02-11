#include<stdio.h>
#include<iostream>
#include<vector>
#include<bitset>

/*
AtCoder Grand Contest 031 C-Differ by 1 Bit
*/

#define MAX_BIN 17

unsigned long long int crop(unsigned long long int num, int a){
    return (num&((1<<a)-1))+((num&(((1<<MAX_BIN)-1)^((1<<(a+1))-1)))>>1);
}
unsigned long long int insert(unsigned long long int num, bool bit,int a){
    return (num&((1<<a)-1))+((num&(((1<<MAX_BIN)-1)^((1<<a)-1)))<<1)+(bit<<a);
}

std::vector<unsigned long long int> GrayCodeGenerator(unsigned long long int a,unsigned long long int b,int binary_digit){
    std::bitset<17> dif(a^b);
    if(dif.count()%2==0){
        std::vector<unsigned long long int> emp={};
        return emp;
    }
    if(binary_digit==1){
        std::vector<unsigned long long int> ans;
        ans.push_back(a);
        ans.push_back(b);
        return ans;
    }
    int dig;
    for(int i=binary_digit-1;i>=0;i--){
        if((a&(1<<i))!=(b&(1<<i)))dig=i;
    }
    unsigned long long int adash=crop(a,dig);
    unsigned long long int bdash=crop(b,dig);
    unsigned long long int c=adash^(1<<(binary_digit-2));
    std::vector<unsigned long long int> p=GrayCodeGenerator(adash,c,binary_digit-1);
    std::vector<unsigned long long int> q=GrayCodeGenerator(c,bdash,binary_digit-1);
    for(unsigned long long int i=0;i<p.size();i++)p[i]=insert(p[i],(a&(1<<dig))>>dig,dig);
    for(unsigned long long int i=0;i<q.size();i++)q[i]=insert(q[i],(b&(1<<dig))>>dig,dig);
    std::copy(q.begin(),q.end(),std::back_inserter(p));
    return p;
}

int main()
{
    int n,a,b;
    scanf("%d %d %d",&n,&a,&b);
    std::vector<unsigned long long int> ans=GrayCodeGenerator(a,b,n);
    if(ans.empty())printf("NO\n");
    else{
        printf("YES\n");
        for(unsigned long long int i : ans){
            printf("%lld\n",i);
        }
    }
    return 0;
}