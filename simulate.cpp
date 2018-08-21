/*
@author: Yiping Ma
*/
#include "simulate.h"

using namespace std;

extern int X[70];

void random_X(int n, int m) {
    set<int> pool;

    int C = 3;
    for (int i = 0; i < C; i++) {
        int rand_n = int(rand() % n);
        pool.insert(rand_n);
    }

    set<int>::iterator iter;

    double prob = max(0.0, 1 - (double(m) / double(n)));
    for (iter = pool.begin(); iter != pool.end(); ++iter) {
        double rand_p = (double)(rand() % 100) / (double)101;
        if (rand_p < prob) {
            X[*iter] = -1;
        } else if (X[*iter] == -1) { 
            int Y[100];
            memset(Y, -1, sizeof(Y));
            int flag = 0, j = 0;
            for (int scan = 0; scan < m; scan++) { 
                flag = 0;
                for (int i = 0; i < n; i++) {
                    if (X[i] == scan) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    Y[j] = scan;
                    j++;
                }
            }

            int t = 1;
            for (int i = 0; i < 100; i++) {
                if (Y[i] == -2) {
                    t = i;
                    break;
                }
            }

            double rand_t = (double)(rand() % 100) / (double)101;
            if (rand_t > prob) {
                //cout << "t = " << t << endl;
                X[*iter] = Y[rand() % t];
            }

        }
    }

    set<int> permpool;
    for (int i = 0; i < C; i++) {
        int rand_n = int(rand() % n);
        permpool.insert(rand_n);
    }
    
    set<int>::iterator it;
    int perm[permpool.size()];
    int i = 0;
    for (it = permpool.begin(); it != permpool.end(); ++it) {
        perm[i++] = X[*it];
    }
   
    random_shuffle(perm, perm + permpool.size());
    i = 0;
    for (it = permpool.begin(); it != permpool.end(); ++it) {
        X[*it] = perm[i++];
    }

}
