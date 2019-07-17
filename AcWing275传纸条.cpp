#include <bits/stdc++.h>
using namespace std;
/**
 * 假设dp[x1, y1, x2, y2]为<x1, y1>的一条路径的值
 * <x2, y2>为另一条路径的值
 * 因为每条路径有两个状态
 * <x1, y1> <x1 - 1, y1> <x1, y1 - 1>
 * <x2, y2> <x2 - 1, y2> <x2, y2 - 1>
 * 故有如下4个状态
 * <x1 - 1, y1, x2 - 1, y2>
 * <x1 - 1, y1, x2, y2 - 1>
 * <x1, y1 - 1, x2 - 1, y2>
 * <x1, y1 - 1, x2, y2 - 1>
 * 
 * 初态
 * dp[0][0][0][0] = 0;
 * 终态
 * dp[n][m][n][m];
 * 
 * 如果到达的状态为dp[i][j][z][h] 如果i == z && j == h,那么会走过相同的通道，所以只能加一次
 * 故转移状态为          dp[i][j][z][h] = max(dp[i][j][z][h], dp[i - 1][j][z - 1][h] + arr[i][j]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i - 1][j][z][h - 1] + arr[i][j]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i][j - 1][z - 1][h] + arr[i][j]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i][j - 1][z][h - 1] + arr[i][j]);
 * 如果步走过相同的通道,那么转移状态为
 *                      dp[i][j][z][h] = max(dp[i][j][z][h], dp[i - 1][j][z - 1][h] + arr[i][j] + arr[z][h]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i - 1][j][z][h - 1] + arr[i][j] + arr[z][h]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i][j - 1][z - 1][h] + arr[i][j] + arr[z][h]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i][j - 1][z][h - 1] + arr[i][j] + arr[z][h]);
 * **/
const int MAXN = 55;
int arr[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];
int n, m;
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            scanf("%d", &arr[i][j]);
        }
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            for(int z = 1; z <= n; z ++){
                for(int h = 1; h <= m; h ++){
                    if(i != z || j != h){
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i - 1][j][z - 1][h] + arr[i][j] + arr[z][h]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i - 1][j][z][h - 1] + arr[i][j] + arr[z][h]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i][j - 1][z - 1][h] + arr[i][j] + arr[z][h]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i][j - 1][z][h - 1] + arr[i][j] + arr[z][h]);
                    }
                    else{
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i - 1][j][z - 1][h] + arr[i][j]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i - 1][j][z][h - 1] + arr[i][j]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i][j - 1][z - 1][h] + arr[i][j]);
                        dp[i][j][z][h] = max(dp[i][j][z][h], dp[i][j - 1][z][h - 1] + arr[i][j]);
                    }
                }
            }
        }
    }
    printf("%d\n", dp[n][m][n][m]);
    return 0;
}