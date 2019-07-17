#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 5;
int arr[MAXN];
int n;
/**
使用三分来尝试一下
**/
double f(double x)
{
    double ans = 0;
    for(int i = 0; i < n; i ++)
    {
        ans += fabs(x - arr[i]);
    }
    return ans;
}
double finds(double ll, double rr)
{
    double l = ll;
    double r = rr;
    double mid, mids;
    while(l + 1e-5 < r)
    {
        mid = (l + r) / 2.0;
        mids = (mid + r) / 2.0;
        if(f(mid) < f(mids))
        {
            r = mids;
        }
        else
        {
            l = mid;
        }
    }
    return l;
}
int main()
{
    scanf("%d", &n);
    int maxs = 0;
    for(int i = 0; i < n; i ++)
    {
        scanf("%d", &arr[i]);
        maxs = max(arr[i], maxs);
    }
    double m = maxs * 1.0;
    double re = finds(0, maxs);
    printf("%.0f\n", f(re));
    return 0;
}