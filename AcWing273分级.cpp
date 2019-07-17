#include <bits/stdc++.h>
using namespace std;
/**
 * dp[i][j]代表在i的长度下，以j为结尾的最小值
 * dp[i][j] = min(dp[i - 1][z] + abs(arr[i] - j));///z <= j
 * **/
const int MAXN = 2005;
typedef long long ll;
const ll inf = __LONG_LONG_MAX__;
ll arr[MAXN];
ll dp[MAXN][MAXN];
void Init(){
    memset(arr, 0, sizeof(arr));
    memset(dp, 0, sizeof(dp));
}
int n;
vector<ll>vec;
int main(){
    scanf("%d", &n);
    Init();
    vec.clear();
    for(int i = 1; i <= n; i ++){
        scanf("%lld", &arr[i]);
        vec.push_back(arr[i]);
    }
    sort(vec.begin(), vec.end());
    for(int i = 1; i <= n; i ++){
        ll temp = dp[i - 1][1];
        for(int j = 1; j <= n; j ++){
            temp = min(temp, dp[i - 1][j]);
            dp[i][j] = temp + abs(arr[i] - vec[j - 1]);///vec从0开始
        }
    }
    ll re = dp[n][1];
    for(int i = 1; i <= n; i ++){
        re = min(dp[n][i], re);
    }
    printf("%lld\n", re);
    return 0;
}