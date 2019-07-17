#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mem(a) memset(a, 0, sizeof(a))
using namespace std;
int n, len, cnt, sum, maxs;
const int MAXN = 105;
int arr[MAXN];
int vids[MAXN];
bool cmp(const int &a, const int &b)
{
    return a > b;
}
bool dfs(int step, int cab, int last)
{
    if(step > cnt)
        return true;
    if(cab == len)
        return dfs(step + 1, 0, 0);
    int fail = 0;
    for(int i = last; i < n; i ++)
    {
        if(!vids[i] && cab + arr[i] <= len && arr[i] != fail)
        {
            vids[i] = 1;
            if(dfs(step, cab + arr[i], i + 1))
                return true;
            fail = arr[i];
            vids[i] = 0;
            if(cab == 0 || cab + arr[i] == len)///如果没有可以选择的，或者拼凑出一根目标长度的木棒，但是剩下来的木棒并不能完成目标，必定是失败的
                return false;
        }
    }
    return false;
}
int main()
{
    while (~scanf("%d", &n) && n)
    {
        int true_n = 0;
        maxs = sum = 0;
        mem(arr);
        mem(vids);
        for(int i = 1; i <= n; i ++)
        {
            int x;
            scanf("%d", &x);
            if(x > 50)
                continue;
            arr[true_n] = x;
            sum += arr[true_n];
            maxs = max(maxs, arr[true_n]);
            true_n ++;
        }
        n = true_n;
        sort(arr, arr + n, cmp);
        for(int i = maxs; i <= sum; i ++)
        {
            if(sum % i == 0)
            {
                cnt = sum / i;
                len = i;
                mem(vids);
                if(dfs(1, 0, 0))
                {
                    printf("%d\n", i);
                    break;
                }
            }
        }
    }
    return 0;
}