#include <bits/stdc++.h>
using namespace std;
/**
 * DP的状态为已经完成的请求数量，通过指派一位服务员
 * 可以把"完成i - 1个请求的状态"转移到"完成i个请求的状态"
 * 那么我们可以知道转移从dp[i - 1] -> dp[i]
 * dp[i][x][y][z] 代表为第i次选择的情况下，对应的1,2,3号服务员
 * 所对应的位置
 * 那么可以得知
 * dp[i][arr[i]][y][z] = min(dp[i][arr[i]][y][z], dp[i - 1][x][y][z] + cost[x][arr[i]])
 * dp[i][x][arr[i]][z] = min(dp[i][x][arr[i]][z], dp[i - 1][x][y][z] + cost[y][arr[i]])
 * dp[i][x][y][arr[i]] = min(dp[i][x][y][arr[i]], dp[i - 1][x][y][z] + cost[z][arr[i]])
 * 
 * 因为肯定有一个位置，继承了上一个的位置
 * 所以保存两个状态就可以了
 * 
 * 三种状态转移 pi,x,y
 * dp[i][x][y] = min(dp[i][x][y], dp[i - 1][x][y] + cost[pi - 1][pi])
 * dp[i][pi][y] = min(dp[i][pi][y], dp[i - 1][x][y] + cost[x][pi])
 * dp[i][x][pi] = min(dp[i][x][pi], dp[i - 1][x][y] + cost[y][pi])
 * 
 * dp[0][1][2] = 0;
 * for(int i = 0; i <= n; i ++)
 * {
 * for(int x = 1; x <= l; x ++)
 * {
 * for(int y = 1; y <= l; y ++)
 * {
 * if(x == y || x == arr[i] || y == arr[i])continue;
 * dp[i + 1][x][y] = min(dp[i][x][y], dp[i][x][y] + cost[pi][pi + 1]);
 * dp[i + 1][pi][y] = min(dp[i][pi][y], dp[i][x][y] + cost[x][pi + 1]);
 * dp[i + 1][x][pi] = min(dp[i][x][pi], dp[i][x][y] + cost[y][pi + 1]);
 * }
 * }
 * }
 * **/
typedef long long ll;
const int MAXN = 205;
int cost[MAXN][MAXN];
int arr[MAXN * 5];
int dp[1005][MAXN][MAXN];
int l, n;
int main(){
    scanf("%d%d", &l, &n);
    for(int i = 1; i <= l; i ++){
        for(int j = 1; j <= l; j ++){
            scanf("%d", &cost[i][j]);
        }
    }
    for(int i = 1; i <= n; i ++){
        scanf("%d", &arr[i]);
    }
    arr[0] = 3;
    for(int i = 0; i <= n; i ++){
        for(int j = 1; j <= l; j ++){
            for(int z = 1; z <= l; z ++){
                dp[i][j][z] = 0x3f3f3f3f;
            }
        }
    }
    dp[0][1][2] = 0;
    for(int i = 0; i < n; i ++){
        for(int x = 1; x <= l; x ++){
            for(int y = 1; y <= l; y ++){
                if(x == y || x == arr[i] || y == arr[i]) continue;
                dp[i + 1][x][y] = min(dp[i + 1][x][y], dp[i][x][y] + cost[arr[i]][arr[i + 1]]);
                dp[i + 1][arr[i]][y] = min(dp[i + 1][arr[i]][y], dp[i][x][y] + cost[x][arr[i + 1]]);
                dp[i + 1][x][arr[i]] = min(dp[i + 1][x][arr[i]], dp[i][x][y] + cost[y][arr[i + 1]]);
            }
        }
    }
    int re = 0x7fffffff;
    for(int x = 1; x <= l; x ++){
        for(int y = 1; y <= l; y ++){
            re = min(re, dp[n][x][y]);
        }
    }
    printf("%d\n", re);
    return 0;
}