#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

using namespace std;
const int n = 8;

int main() {
    int L[22][22] = {0}, i, j;
    ifstream fin("input.txt");
    for (i = 1; i <= n;i++) {
        for (j = 1; j <= n; j++) {
            fin >> L[i][j];
        }
    }
    fin.close();

    for (j = 0; j <= n + 1; j++) {
        L[0][j] = -1;
        L[n + 1][j] = -1;
    }
    for (i = 1; i <= n; i++) {
        L[i][0] = -1;
        L[i][n + 1] = -1;
    }
    int si, sj, fi, fj;
    cin >> si >> sj;
    cin >> fi >> fj;

    if (L[si][sj] == -1 || L[fi][fj] == -1) {
        cout << "Cannot reach the end point" << endl;
        return 0;
    }
    int Pi[401], Pj[401], r, t;
    
    Pi[1] = si;
    Pj[1] = sj;
    r = 1;          // 队列尾部
    t = 1;          // 队列头部
    L[si][sj] = 1;  // 起点步数为1

    while (t <= r) {// BFS    
        i = Pi[t];
        j = Pj[t];
        int q = L[i][j] + 1;  // 下一步的步数

        if (L[i - 1][j] == 0) {
            L[i - 1][j] = q;
            r++;
            Pi[r] = i - 1;
            Pj[r] = j;
        }
        if (L[i][j - 1] == 0) {
            L[i][j - 1] = q;
            r++;
            Pi[r] = i;
            Pj[r] = j - 1;
        }
        if (L[i + 1][j] == 0) {
            L[i + 1][j] = q;
            r++;
            Pi[r] = i + 1;
            Pj[r] = j;
        }
        if (L[i][j + 1] == 0) {
            L[i][j + 1] = q;
            r++;
            Pi[r] = i;
            Pj[r] = j + 1;
        }
        if (L[i - 1][j - 1] == 0) {
            L[i - 1][j - 1] = q;
            r++;
            Pi[r] = i - 1;
            Pj[r] = j - 1;
        }
        if (L[i - 1][j + 1] == 0) {
            L[i - 1][j + 1] = q;
            r++;
            Pi[r] = i - 1;
            Pj[r] = j + 1;
        }
        if (L[i + 1][j - 1] == 0) {
            L[i + 1][j - 1] = q;
            r++;
            Pi[r] = i + 1;
            Pj[r] = j - 1;
        }
        if (L[i + 1][j + 1] == 0) {
            L[i + 1][j + 1] = q;
            r++;
            Pi[r] = i + 1;
            Pj[r] = j + 1;
        }
        t++;
    }
    if (L[fi][fj] == 0) {
        cout << "Cannot reach the end point" << endl;
        return 0;
    }

    int Mi[401], Mj[401], k;
    bool path[22][22] = { false };
    k = L[fi][fj]; i = fi; j = fj;  // 从终点往回走
    while (k > 0)
    {
        Mi[k] = i; Mj[k] = j;  // 记录当前点
        if (L[i - 1][j] > 0 && L[i - 1][j] < L[i][j]) i--;
        else if (L[i][j - 1] > 0 && L[i][j - 1] < L[i][j]) j--;
        else if (L[i + 1][j] > 0 && L[i + 1][j] < L[i][j]) i++;
        else if (L[i][j + 1] > 0 && L[i][j + 1] < L[i][j]) j++;
        else if (L[i - 1][j - 1] > 0 && L[i - 1][j - 1] < L[i][j]) { i--; j--; }
        else if (L[i - 1][j + 1] > 0 && L[i - 1][j + 1] < L[i][j]) { i--; j++; }
        else if (L[i + 1][j - 1] > 0 && L[i + 1][j - 1] < L[i][j]) { i++; j--; }
        else if (L[i + 1][j + 1] > 0 && L[i + 1][j + 1] < L[i][j]) { i++; j++; }
        k--;
    }
    for (int a = 1; a <= L[fi][fj]; a++) {
        path[Mi[a]][Mj[a]] = true;
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (L[i][j] == -1) {
                cout << '#';
            }
            else if (path[i][j]) {
                cout << '*';
            }
            else {
                cout << '-';
            }
        }
        cout << endl;
    }
    cout << "Shortest path step count：" << L[fi][fj] << endl;

}