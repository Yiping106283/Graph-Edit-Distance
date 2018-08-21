/*
@author: Mingjia Huo
*/
#include "simulate.h"

using namespace std;

#define MAX 20000

extern int node1, node2;
extern int nv1[70], nv2[70], ev1[70][70], ev2[70][70];

int cns, cndi, ces, cedi = 0;
int X[70] = {};

struct element {    //用来排序的数据结构
    int data;  // 数据
    int index;  // 序号
};

int cmp(const void* a, const void* b) { // 升序排序
    return ((struct element*)a)->data - ((struct element*)b)->data;

}

void rand_of_n(int a[], int n) {
    int i;
    struct element ele[MAX];
    srand((int)time(0));  // 初始化随机数种子
    for (i = 0; i < n; i++) {
        ele[i].data = rand(); // 随机生成一个数
        ele[i].index = i;
    }
    qsort(ele, n, sizeof(ele[0]), cmp); //排序
    for (i = 0; i < n; i++) {
        a[i] = ele[i].index;
    }
}

void init(int n, int m) {
    srand((unsigned)time(NULL));
    if (n >= m) {
        rand_of_n(X, n);
        for (int i = 0; i < n; ++i) {
            if (X[i] >= m)X[i] = -1;
        }

    } else {
        rand_of_n(X, m);
    }
}



int cost();
int cost0(int X0[70]){
	for(int i=0;i<70;++i){
    if(X0[i]!=-1)
    X0[i]--;
}
    memcpy(X, X0, sizeof(int)*70);
    //cout<<"cost000000  ="<<cost()<<endl;
    return 0;
}

int cost() {
/*for(int i=0;i<node1;++i){
cout<<X[i]<<" ";
}cout<<endl;*/
    int n = node1;
    int m = node2;
    bool vis[140];
    bool vise[140][140];
    int ret = 0;
    memset(vis, false, sizeof(bool) * 140);
    memset(vise, false, sizeof(bool) * 140 * 140);
    for (int i = 0; i < n; ++i) {
        int j = X[i];
        if (j == -1) ret += cndi;
        else {
            vis[j] = true;
            if (nv1[i] != nv2[j])
                ret += cns;
        }
    }
//cout<<ret<<endl;
    for (int i = 0; i < m; ++i)
        if (!vis[i]) ret += cndi;
//cout<<ret<<endl;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (ev1[i][j] != -1) {
                int k = X[i], l = X[j];
//cout<<"k="<<k<<" l="<<l<<endl;
                if (k == -1 || l == -1 || ev2[k][l] == -1)
                    ret += cedi;
                else {
                    vise[k][l] = vise[l][k] = true;
                    if (ev2[k][l] != ev1[i][j])
                        ret += ces;
                }
            }
//cout<<ret<<endl;
    for (int i = 0; i < m; ++i)
        for (int j = i + 1; j < m; ++j)
            if (ev2[i][j] != -1 && !vise[i][j])
                ret += cedi;
//cout<<ret<<endl;
    return ret;
}



