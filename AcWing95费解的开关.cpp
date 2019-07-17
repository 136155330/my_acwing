#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
/**
 状态压缩dp尝试下
 从DP[1 << 25]进行压缩
 逆向dfs，那么从(1 << 25 - 1)
 dp[(1 << 25 - 1)] = 0;
 **/
char dp[(1 << 25) + 1];
int vids[10][10];
int n;
int maps[10][10];
char m[10][10];
int moves[5][2] = {{0, 0},{0, 1},{0, -1},{1, 0},{-1, 0}};
void Init()
{
    memset(vids, 0, sizeof(vids));
    for(int i = 1; i <= 5; i ++)
        for(int j = 1; j <= 5; j ++)
            maps[i][j] = 1;
}
void change(int i, int j)
{
    for(int ii = 0; ii < 5; ii ++)
    {
        int x = i + moves[ii][0];
        int y = j + moves[ii][1];
        maps[x][y] = !maps[x][y];
    }
}
int jzchang()
{
    int sum = ((1 << 25) - 1);///25位的1
    int num = 0;
    for(int i = 5; i != 0; i --)
    {
        for(int j = 5; j != 0; j --)
        {
            if(maps[i][j] == 0)
            {
                sum = sum ^ (1 << num);
            }
            num ++;
        }
    }
    return sum;
}
void dfs(int step)
{
    if(step == 6)
    {
        return;
    }
    for(int i = 1; i <= 5; i ++)
    {
        for(int j = 1; j <= 5; j ++)
        {
            if(vids[i][j] == 0)
            {
                vids[i][j] = 1;
            change(i, j);
            long long temp = jzchang();
            if(dp[temp] == 'a')
            {
                dp[temp] = step + 1 + '0';
                dfs(step + 1);
            }
            change(i, j);
                vids[i][j] = 0;
            }
        }
    }
}
int main()
{
    scanf("%d", &n);
    Init();
    for(int i = 0; i < (1 << 25) + 1; i ++)
        dp[i] = 'a';
    dp[(1 << 25) - 1] = '0';///初始状态为0
    dfs(0);
    while(n --)
    {
        for(int i = 1; i <= 5; i ++)
            scanf("%s", m[i]);
        for(int i = 1; i <= 5; i ++)
        {
            for(int j = 0; j < 5; j ++)
            {
                maps[i][j + 1] = m[i][j] - '0';
            }
        }
        long long t = jzchang();
        if(dp[t] == 'a')
            printf("-1\n");
        else
            printf("%d\n", dp[t] - '0');
    }
    return 0;
}

