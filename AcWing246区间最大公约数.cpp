#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 500000 + 5;
int n, m;
/**
 * gcd(a, b, c, d, e, f) = gcd(a, b - a, c - b, d - c, e - d, f - e)
 * gcd(a, -b) = gcd(a, b)
 * 构造单点更新线段树
 * 来维护差分序列，这样的话每次查询gcd([l, r])只要查询gcd(a + ask(a), query(l, r))
 * **/
struct SEGTREE{
    ll arr[MAXN];
    ll brr[MAXN];
    struct NODE{
        ll l, r;
        ll sum, gcd_sum;
    }tree[MAXN << 2];
    void push_up(ll root){
        ll a = abs(tree[root << 1].gcd_sum);
        ll b = abs(tree[root << 1 | 1].gcd_sum);
        tree[root].gcd_sum = __gcd(a, b);
        tree[root].sum = tree[root << 1].gcd_sum + tree[root << 1 | 1].gcd_sum;
    }
    void build(ll root, ll l, ll r){
        tree[root].l = l;
        tree[root].r = r;
        int mid = (l + r) >> 1;
        if(l == r){
            tree[root].gcd_sum = tree[root].sum = brr[l];
            return ;
        }
        build(root << 1, l, mid);
        build(root << 1 | 1, mid + 1, r);
        push_up(root);
    }
    void update(ll root, ll num, ll val){
        if(tree[root].l == tree[root].r){
            tree[root].sum += val;
            tree[root].gcd_sum += val;
            return ;
        }
        ll mid = (tree[root].l + tree[root].r) >> 1;
        if(num <= mid){
            update(root << 1, num, val);
        }
        else{
            update(root << 1 | 1, num, val);
        }
        push_up(root);
    }
    ll query(ll root, ll l, ll r){
        if(l > r)
            return 0;
        ll mid = (tree[root].l + tree[root].r) >> 1;
        if(tree[root].l == l && tree[root].r == r){
            return abs(tree[root].gcd_sum);
        }
        if(r <= mid){
            return abs(query(root << 1, l, r));
        }
        else if(l > mid){
            return abs(query(root << 1 | 1, l, r));
        }
        else{
            return abs(__gcd(query(root << 1, l, mid), query(root << 1 | 1, mid + 1, r)));
        }
    }
}seg1;
struct Tree_arr{
    /**
     * 涉及数状数组的高级应用
     * 使用一个初始的数组b，全为空
     * arr数组记录初始值
     * 那么查询单点的时候值为a[i] + ask(i)
     * **/
    ll crr[MAXN << 1];
    void Init(){
        memset(crr, 0, sizeof(crr));
    }
    void add(ll x, ll y){
        for(; x <= n; x += (x & -x)){
            crr[x] += y;
        }
    }
    ll ask(ll x){
        ll ans = 0;
        for(; x; x -= (x & -x)){
            ans += crr[x];
        }
        return ans;
    }
}teg;
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++){
        scanf("%lld", &seg1.arr[i]);
    }
    seg1.brr[1] = seg1.arr[1];
    for(int i = 2; i <= n; i ++){
        seg1.brr[i] = seg1.arr[i] - seg1.arr[i - 1];
    }
    seg1.build(1, 1, n);
    teg.Init();
    char s[2];
    for(int i = 0; i < m; i ++){
        scanf("%s", &s);
        if(s[0] == 'Q'){
            ll a, b;
            scanf("%lld%lld", &a, &b);
            printf("%lld\n", __gcd(seg1.arr[a] + teg.ask(a), seg1.query(1, a + 1, b)));
        }
        else{
            ll a, b, val;
            scanf("%lld%lld%lld", &a, &b, &val);
            seg1.update(1, a, val);
            teg.add(a, val);
            if(b != n){
                seg1.update(1, b + 1, -val);
                teg.add(b + 1, -val);
            }
        }
    }
    return 0;
}