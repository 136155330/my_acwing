#include <bits/stdc++.h>
#define mem(x) memset(x, 0, sizeof(x))
using namespace std;
const int MAXN = 205;
int drr[MAXN], prr[MAXN], dp[25][805], lujing[25][805][500];
void Init(){
    mem(drr), mem(prr), mem(dp), mem(lujing);
    for(int i = 0; i < 25; i ++){
        for(int j = 0; j < 805; j ++){
            dp[i][j] = -1;
        }
    }
    dp[0][400] = 0;
}
int n, m;
int main(){
    int step = 0;
    while(cin >> n >> m && (n || m)){
        Init();
        for(int i = 1; i <= n; i ++){
            cin >> drr[i] >> prr[i];
        }
        for(int i = 1; i <= n; i ++){
            for(int j = m; j > 0; j --){
                ///因为drr[i] - prr[i]会存在 < 0的情况
                ///按照原来的转移方程 k = 0; k <= 400; k ++
                ///dp[0][0]选了0个dsum - rsum = 0 为 1
                ///dp[m][k - (d[i] - r[i])] + d[i] + r[i]
                ///会出现负数，导致状态转移是错误的
                ///k = 0; k <= 800; k ++
                ///if(k - (d[i] - r[i]) >= 0 && dp[j - 1][k - (d[i] - r[i])] >= 0)
                for(int k = 0; k <= 800; k ++){
                    if(k - (drr[i] - prr[i]) >= 0 && dp[j - 1][k - (drr[i] - prr[i])] >= 0 && k - (drr[i] - prr[i]) <= 800){
                        if(dp[j - 1][k - (drr[i] - prr[i])] + drr[i] + prr[i] > dp[j][k]){
                            dp[j][k] = dp[j - 1][k - (drr[i] - prr[i])] + drr[i] + prr[i];
                            lujing[j][k][dp[j][k]] = i;
                        }
                    }
                }
            }
        }
        int sum = 0x7fffffff;/// a - b
        int num = 0;/// a + b
        int re = 0;
        int flag = 0;
        for(int k = 0; k <= 800; k ++){
            if(k <= 400){
                int temp = 400 - k;
                if(temp < sum && dp[m][k] >= 0){
                    sum = temp;
                    num = dp[m][k];
                    re = k;
                    flag = 0;
                }
                else if(temp == sum && dp[m][k] >= num){
                    num = dp[m][k];
                    re = k;
                    flag = 0;
                }
            }
            else{
                int temp = k - 400;
                if(temp < sum && dp[m][k] >= 0){
                    sum = temp;
                    num = dp[m][k];
                    re = k;
                    flag = 1;
                }
                else if(temp == sum && dp[m][k] >= num){
                    num = dp[m][k];
                    re = k;
                    flag = 1;
                }
            }
        }
        int a, b;
        if(flag == 1){
            a = (sum + num) / 2;
            b = num - a;
        }
        else{
            a = (num - sum) / 2;
            b = num - a;
        }
        printf("Jury #%d\n", ++ step);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", a, b);
        vector<int>vec;
        vec.clear();
        int k = re;
        int mysum = dp[m][k];
        while(lujing[m][k][mysum]){
            vec.push_back(lujing[m][k][mysum]);
            int temp = lujing[m][k][mysum];
            m --;
            k = k - (drr[temp] - prr[temp]);
            mysum = mysum - drr[temp] - prr[temp];
        }
        sort(vec.begin(), vec.end());
        for(int i = 0; i < vec.size(); i ++){
            printf(" %d", vec[i]);
        }
        printf("\n\n");
    }
    return 0;
}