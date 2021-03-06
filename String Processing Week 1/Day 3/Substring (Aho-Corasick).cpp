//https://vjudge.net/contest/488773#problem/T

#include <bits/stdc++.h>

using namespace std;


const int N = int(4e2) + 9, ALPHA = 128;
char childChars[N][ALPHA];
int child[N][ALPHA], fail[N], nxt[N], patID[N], cCharsSz[N], numNodes;

int addNode() {
    memset(child[numNodes], -1, sizeof child[numNodes]);
    patID[numNodes] = -1;
    cCharsSz[numNodes] = 0;
    return numNodes++;
}

void init() {
    numNodes = 0;
    addNode();
}

int insert(char *pat, int ID) {
    int cur;
    for (cur = 0; *pat; pat++) {
        char c = *pat;
        int &nd = child[cur][c];
        if (!~nd) {
            nd = addNode();
            childChars[cur][cCharsSz[cur]++] = c;
        }
        cur = nd;
    }
    return ~patID[cur] ? patID[cur] : (patID[cur] = ID);
}

int nxtF(int f, char c) {
    while (!~child[f][c])
        f = fail[f];
    f = child[f][c];
    return f;
}

void computeFail() {
    queue<int> q;
    for (int i = 0; i < ALPHA; i++) {
        int &nd = child[0][i];
        if (~nd)
            fail[nd] = nxt[nd] = 0, q.push(nd);
        else nd = 0;
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < cCharsSz[u]; i++) {
            char c = childChars[u][i];
            int v = child[u][c];
            fail[v] = nxt[v] = nxtF(fail[u], c);
            q.push(v);
        }
    }
}

int Nxt(int u) {
    if (!u) return u;
    int &v = nxt[u];
    return ~patID[v] ? v : v = Nxt(v);
}

void printTrie() {
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < cCharsSz[i]; j++) {
            char c = childChars[i][j];
            int x = child[i][c];
            cout << i << "," << nxt[i] << " " << x << "," << nxt[x] << " " << c << endl;
        }
    }
    for (int i = 1; i < numNodes; i++) {
        int x = fail[i];
        cout << i << "," << nxt[i] << " " << x << "," << nxt[x] << endl;
    }

}

char pat[21];
double dp[401][101];
char ch[62];
double pr[62];
int n;

double solve(int ni, int rem) {
    for (int i = ni; i; i = Nxt(i))
        if (~patID[i]) return 0;
    if (!rem) return 1;
    double &ret = dp[ni][rem];
    if (ret == ret) return ret;
    ret = 0;
    for (int i = 0; i < n; i++)
        ret += pr[i] * solve(nxtF(ni,ch[i]),rem - 1);
    return ret;
}

int main() {
    int t, tc = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        init();
        while (n--) {
            scanf("%s", pat);
            insert(pat, n);
        }
        memset(dp, -1, sizeof dp);
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf(" %c%lf", &ch[i], &pr[i]);
        int lm;
        scanf("%d", &lm);
        computeFail();
        printf("Case #%d: %.6lf\n", tc++, solve(0, lm));

    }
    return 0;
}
