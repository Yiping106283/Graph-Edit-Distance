#include "simulate.h"

using namespace std;

extern int X[70];

void random_X(int n, int m) {
    set<int> pool;

    // 取出至多C位
    int C = 3;
    for (int i = 0; i < C; i++) {
        int rand_n = int(rand() % n);
        pool.insert(rand_n);
    }

    // 对每一位，以prob的概率变成-1
    set<int>::iterator iter;

    //cout << m << " " << n << endl;
    double prob = max(0.0, 1 - (double(m) / double(n)));
    //cout << "prob = " << prob << endl;
    for (iter = pool.begin(); iter != pool.end(); ++iter) {
        //cout << "*iter = " << *iter << endl;
        double rand_p = (double)(rand() % 100) / (double)101;
        if (rand_p < prob) {
            X[*iter] = -1;
        } else if (X[*iter] == -1) { // 如果该位是-1，以1-p的概率变成别的
            int Y[100];
            memset(Y, -1, sizeof(Y));

            int flag = 0, j = 0;
            for (int scan = 0; scan < m; scan++) { //这里是m？
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

            // 计算t
            int t = 1;
            for (int i = 0; i < 100; i++) {
                if (Y[i] == -2) {
                    t = i;
                    break;
                }
            }

            double rand_t = (double)(rand() % 100) / (double)101;
            //cout << "rand_t = " << rand_t << endl;
            if (rand_t > prob) {
                //cout << "t = " << t << endl;
                X[*iter] = Y[rand() % t];
            }

        }
    }


    // 再至多取C位
    set<int> permpool;
    for (int i = 0; i < C; i++) {
        int rand_n = int(rand() % n);
        permpool.insert(rand_n);
    }
    // 把这小于等于C位做一下置换
    set<int>::iterator it;
    int perm[permpool.size()];
    int i = 0;
    for (it = permpool.begin(); it != permpool.end(); ++it) {
        //cout << "*it = " << *it << " ";
        perm[i++] = X[*it];
    }
    // << endl;

    // 把这C位塞回去

    random_shuffle(perm, perm + permpool.size());
    i = 0;
    for (it = permpool.begin(); it != permpool.end(); ++it) {
        X[*it] = perm[i++];
    }

}
