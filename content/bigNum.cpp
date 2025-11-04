#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define task ""
#define booster() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
typedef vector<int> bignum;
bignum add(bignum a,bignum b) {
    bignum c;
    c.resize(max(a.size(),b.size()));
    a.resize(c.size());
    b.resize(c.size());
    int mem=0;
    for (int i=0; i<c.size(); ++i){
        int sum=mem+a[i]+b[i];
        c[i]=sum%10;
        mem=sum/10;
    }
    if (mem>0) c.push_back(mem);
    return c;
}
bignum subtract(bignum a,bignum b) {
    bignum c;
    c.resize(max(a.size(),b.size()));
    a.resize(c.size());
    b.resize(c.size());
    int mem=0;
    for (int i=0; i<c.size(); ++i){
        int sub=a[i]-b[i]-mem;
        if (sub<0){
            mem=1;
            sub+=10;
        }
        else mem = 0;
        c[i]=sub;
    }
    while (c.size()>1 and c[c.size()-1]==0) c.pop_back();
    return c;
}
bignum multiple(bignum a, int b) {
    bignum c;
    c.resize(a.size());
    int mem=0;
    for (int i=0; i<c.size(); ++i){
        int mul=mem+a[i]*b;
        c[i]=mul%10;
        mem=mul/10;
    }
    while (mem>0){
        c.push_back(mem%10);
        mem/=10;
    }
    return c;
}
bignum multiplebig(bignum a, bignum b) {
    bignum c,cnt;
    c.clear();
    c.push_back(0);
    cnt.clear();
    int mem=0;
    for (int i=0; i<b.size(); ++i){
        bignum tmp = multiple(a,b[i]);
        tmp.insert(tmp.begin(),cnt.begin(),cnt.end());
        c=add(c,tmp);
        cnt.push_back(0);
    }
    return c;
}
bignum division(bignum a, int b) {
    bignum c;
    c.resize(a.size());
    int mem=0;
    for (int i=c.size()-1; i>=0; i--){
        int div=mem*10+a[i];
        c[i]=div/b;
        mem=div%b;
    }
    while (c.size()>1 and c[c.size()-1]==0) c.pop_back();
    return c;
}
int mod(bignum a, int b) {
    int mem=0;
    for (int i=a.size()-1; i>=0; i--){
        int div=mem*10+a[i];
        mem=div%b;
    }
    return mem;
}

bignum tobignum(string a){
    bignum c;
    c.clear();
    for (int i=a.size()-1; i>=0; i--){
        c.push_back(a[i]-48);
    }
    return c;
}

string tostring(bignum a){
    string s="";
    for (int i=a.size()-1; i>=0; i--){
        s+=char(a[i]+48);
    }
    return s;
}

int gcd(int a, int b){
    if (!a)
        return b;
    return gcd(b % a, a);
}
 
int reduceB(int a, string b){
    int mod = 0;
 
    for (int i = 0; i < b.size(); i++)
        mod = (mod * 10 + b[i] - '0') % a;
 
    return mod; 
}

int gcdLarge(int a, string b){
   
    int num = reduceB(a, b);

    return gcd(a, num);
}
 

bool cmp(string a, string b){
    return a.size() < b.size();
}
string s[106];
signed main(){
    booster()
    if (fopen(task".INP", "r")){
        freopen(task".INP", "r", stdin);
        freopen(task".OUT", "w", stdout);
    }
    bignum tich = tobignum("1"), tich1 = tobignum("1"), c;
    int a, a1;
    int n;
    cin >> n;
    for (int i = 1 ; i <= n ; i++){
        cin >> s[i];
        c = tobignum(s[i]);
    }
    sort(s + 1, s + n + 1, cmp);
    a = stoll(s[1]);
    string b = s[2], s1;
    tich = multiple(tobignum(b), a);
    a = gcdLarge(a , b);
    tich = division(tich , a);
    for (int i = 3; i <= n ; i++){
        string b = s[i];
        string s2 = to_string(a);
        a = gcdLarge(a, b);
        tich1 = multiplebig(tobignum(s2) , tobignum(b));
        s1 = tostring(tich1);
        a1 = gcdLarge(stoll(s1) , tostring(tich));
        tich = division(multiplebig(tich1 , tich) , a1);
    }
    if (a != 5){
        tich = division(tich, a);
    }
    if (a % 100 == 0){
        tich = multiple(tich, 2);
    }
    cout<<a<<'\n';
    cout<<tostring(tich);
    return 0;
}