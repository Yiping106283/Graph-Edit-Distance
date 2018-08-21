#include "simulate.h"

#define BIAS -0.5
#define inf 100

using namespace std;

extern int node1, node2;
extern int cns, cndi, ces, cedi;
extern int nv1[70], nv2[70], ev1[70][70],ev2[70][70];
extern int X[70];

extern int read_file1(char* g);
extern int read_file2(char* g);
extern bool exchange();
extern void random_X(int n, int m);
extern void init(int n, int m);
extern int cost();
extern int cost0(int X[]);

clock_t start_time;
clock_t mid_time;
clock_t end_time;
int ifsub = 0;
int count2 = 0;
bool ifchange;
double Temperature = 3000;
double ratio = 0.995;
int cntmod = 50000;
double current = 0.0;

double jump(int c0, int cx, int node1, int node2) {
    double delta = abs(c0 - cx);
    double prob = exp(-delta * 3 / Temperature);
    count2++;
    return prob;
}

void rechange() {
    /*for(int i=0;i<node1;++i){
	cout<<X[i]<<" ";
	};cost();*/
    if (ifchange == false) {
	//cout<<"false"<<endl;
        for (int i = 0; i < node1; ++i) {
            if (X[i] != -1) {
                X[i] += 1;
            }
        }//cost();
        return;
    }
    int y[70] = {};
    for (int i = 0; i < node2; ++i) {
        y[i] = -1;
    }
    for (int i = 0; i < node1; ++i) {
        if (X[i] != -1) {
            y[X[i]] = i + 1;
        }
    }
    memcpy(X, y, sizeof(int) * 70);
    int tmpnode = 0;
    int tmpnv[70] = {};
    int tmpev[70][70] = {};

int len = sizeof(int) * 70;
int area = sizeof(int) * 70 * 70;
    memcpy(tmpnv, nv1, len);
    memcpy(nv1, nv2, len);
    memcpy(nv2, tmpnv, len);
    memcpy(tmpev, ev1, area);
    memcpy(ev1, ev2, area);
    memcpy(ev2, tmpev, area);
    tmpnode = node1;
    node1 = node2;
    node2 = tmpnode;
}

int doit(int Y[]) {
    count2 = 0;
    Temperature = 3000;
    ratio = 0.995;
    int c0 = 0, cx = 0;
    c0 = cost();
    int X0[70] = {};
    int Xmin[70] = {};
    memcpy(Xmin, X, sizeof(int) * 70);
    int mincost = c0;
    int count = 0;
    int cnt_max = cntmod / 10;
    int cnt2_max = 8000;
    while (current < 29) {
        memcpy(X0, X, sizeof(int) * 70);
        random_X(node1, node2);
        cx = cost();
        if (cx < c0) {
            c0 = cx;
            if (c0 < mincost) {
                count2 = 0;
                mincost = c0;
                memcpy(Xmin, X, sizeof(int) * 70);
            }
        } else {
            double prob2 = jump(c0, cx, node1, node2);
            double rand_d = (double)(rand() % 10000) / (double)10000;
            if (rand_d < prob2)
                c0 = cx;
            else
                memcpy(X, X0, sizeof(int)*node1);
            if (count2 > cnt2_max || count == cnt_max) {
                count = 0;
                double rate = abs((double)count2 / cntmod + BIAS );
                cnt_max = (1 - 1.9 * rate) * 2 * cntmod;
                Temperature *= ratio;

            }
        }
        mid_time = clock();
        current = static_cast<double>(mid_time - start_time) / CLOCKS_PER_SEC;
        if (Temperature < 1e-6)break;
    }
    memcpy(X, Xmin, sizeof(int) * 70);
    memcpy(Y, X, sizeof(int) * 70);
    //cout<<mincost<<endl;
    return mincost;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    start_time = clock();
    cns = atoi(argv[1]);
    cndi = atoi(argv[2]);
    ces = atoi(argv[3]);
    cedi = atoi(argv[4]);
    char* g1 = argv[5];
    char* g2 = argv[6];
    ifsub = 0;
    if (cedi * 2 < ces)
        ces = cedi * 2;
    read_file1(g1);
    read_file2(g2);
    if (node1 == 0 || node2 == 0) {
        cout << "Wrong filename or no content in the file." << endl;
        return 0;
    }
    ifchange = exchange();
    int interation = 0;
    int finalcost = 100000;
    int finalx[70] = {};
    int Y[70] = {};
    while (current < 27 && interation < 3) {
        interation++;
	//cout<<"interation"<<endl;
        init(node1, node2);
        int thiscost = doit(Y);
        if (finalcost > thiscost) {
            finalcost = thiscost;
            memcpy(finalx, Y, sizeof(int) * 70);
        }
    }
    memcpy(X, finalx, sizeof(int)*70);
    cost();
    rechange();
    cout<<"2;";
    //cout << finalcost << ";";
    end_time = clock();
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC << ";";
    for (int i = 0; i < node1; ++i)
        cout << X[i] << " ";
    cout << endl;
	/*if(ifchange)cost0(X);
	else{
		for (int i = 0; i < node1; ++i)
        	if(X[i]!=-1) X[i]-=1;
		cost();
}*/
    return 0;
}
