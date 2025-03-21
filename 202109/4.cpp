/**
 * @file 4.cpp
 * @author qzylalala
 * @brief 状态DP, 现场做出来了, 感觉挺套路的。
 * @version 0.1
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 16, M = 1 << N;

int n, m;
double p[N];
double f[M][N * 5 + 1];

double dp(int state, int coins, int r) {//二进制表示每种安排选没选中的状态 r表示还没有的卡牌种类
    auto& v = f[state][coins];//v就是最终的期望：要抽取卡牌的次数
    if (v >= 0) return v;
    if (coins >= r * m) return v = 0;

    v = 0;
    for (int i = 0; i < n; i ++ )
        //第i种卡牌已经被选中
        if (state >> i & 1)
            v += p[i] * (dp(state, coins + 1, r) + 1);
        else
            //state | (1 << i)让第i种卡牌被选中
            v += p[i] * (dp(state | (1 << i), coins, r - 1) + 1);

    return v;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++ ) scanf("%lf", &p[i]);
    //初始化f数组每个元素是-1
    memset(f, -1, sizeof f);

    printf("%.10lf\n", dp(0, 0, n));

    return 0;
}
