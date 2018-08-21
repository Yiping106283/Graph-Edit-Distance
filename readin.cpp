#include "simulate.h"
using namespace std;

const int len = sizeof(int) * 70;
const int area = sizeof(int) * 70 * 70;

int node1, node2;
int nv1[70] = {0};
int nv2[70] = {0};
int ev1[70][70] = {0};
int ev2[70][70] = {0};

static ifstream gxl;

int get_value(string s, int l, int flag) {//flag==1: edge
    int i = 0;
    int v = -1;
    char temp[10] = {};
    while (i < l - 2) {
        if (s[i] == '<' && s[i + 1] == 'i') {
            for (int j = 5; s[j + i] != '<'; ++j) {
                temp[j - 5] = s[i + j];
            }
            v = atoi(temp);
            return v;
        } else if (flag == 0 && s[i] == '<' && s[i + 1] == 's') {
            v = s[i + 8] - 65;
            if (s[i + 9] != '<')
                v = v * 30 + s[i + 9];
            return v;
        }
        i++;
    }
    return v;
}

int value(string s, int l, int flag) {//flag==1: edge
    int ret = get_value(s, l, flag);
    if (ret == -1) {//if value is not in this line, try next line
        getline(gxl, s);
        l = s.length();
        ret = get_value(s, l, flag);
    }
    return ret;
}

int find_edge_index(char* name1, char allname[70][10], int cnt) {
    for (int k = 0; k < cnt; ++k) {
        if (strcmp(name1, allname[k]) == 0) {
            return k;
        }
    }
    return -1;
}

int read_file1(char* g) {
    gxl.open(g);
    string s;
    char node_name[70][10] = {};

    for (int i = 0; i < 70; ++i)
        for (int j = 0; j < 70; ++j) {
            ev1[i][j] = -1;
        }
    int cntnode = 0;
    int cntedge = 0;
    while (getline(gxl, s)) {
        if (s[1] == 'g' && s[2] == 'r')
            break;
    }//begin graph

    int l = 0;
    char tmpname1[10] = {}, tmpname2[10] = {};
    int x = 0, y = 0;
    while (getline(gxl, s)) {
        if (s[1] == 'n') {//new node
            l = s.length();
            int i = 9;
            while (s[++i] != '\"') {
                node_name[cntnode][i - 10] = s[i];
            }
            node_name[cntnode][i - 10] = '\0';
            nv1[cntnode] = value(s, l, 0);
            cntnode++;
        } else if (s[1] == 'e') {//new edge
            int i = 11;
            int l1 = 0, l2 = 0;
            while (s[++i] != '\"') {//first node
                tmpname1[l1++] = s[i];
            }
            tmpname1[l1] = '\0';
            while (s[++i] != '\"');
            while (s[++i] != '\"') {//second node
                tmpname2[l2++] = s[i];
            }
            tmpname2[l2] = '\0';
            x = find_edge_index(tmpname1, node_name, cntnode);
            y = find_edge_index(tmpname2, node_name, cntnode);
            ev1[x][y] = value(s, s.length(), 1);
            ev1[y][x] = ev1[x][y];
            cntedge++;
        }
    }
    node1 = cntnode;
    gxl.close();
    return 0;
}


int read_file2(char* g) {
    gxl.open(g);
    string s;
    char node_name[70][10] = {};

    for (int i = 0; i < 70; ++i)
        for (int j = 0; j < 70; ++j) {
            ev2[i][j] = -1;
        }
    int cntnode = 0;
    int cntedge = 0;
    while (getline(gxl, s)) {
        if (s[1] == 'g' && s[2] == 'r')
            break;
    }//begin graph

    int l = 0;
    char tmpname1[10] = {}, tmpname2[10] = {};
    int x = 0, y = 0;
    while (getline(gxl, s)) {
        if (s[1] == 'n') {//new node
            l = s.length();
            int i = 9;
            while (s[++i] != '\"') {
                node_name[cntnode][i - 10] = s[i];
            }
            node_name[cntnode][i - 10] = '\0';
            nv2[cntnode] = value(s, l, 0);
            cntnode++;
        } else if (s[1] == 'e') {//new edge
            int i = 11;
            int l1 = 0, l2 = 0;
            while (s[++i] != '\"') {//first node
                tmpname1[l1++] = s[i];
            }
            tmpname1[l1] = '\0';
            while (s[++i] != '\"');
            while (s[++i] != '\"') {//second node
                tmpname2[l2++] = s[i];
            }
            tmpname2[l2] = '\0';
            x = find_edge_index(tmpname1, node_name, cntnode);
            y = find_edge_index(tmpname2, node_name, cntnode);
            ev2[x][y] = value(s, s.length(), 1);
            ev2[y][x] = ev2[x][y];
            cntedge++;
        }
    }
    node2 = cntnode;
    gxl.close();
    return 0;
}

bool exchange() {
    if (node1 >= node2) return false;
    int tmpnode = 0;
    int tmpnv[70] = {};
    int tmpev[70][70] = {};
    memcpy(tmpnv, nv1, len);
    memcpy(nv1, nv2, len);
    memcpy(nv2, tmpnv, len);
    memcpy(tmpev, ev1, area);
    memcpy(ev1, ev2, area);
    memcpy(ev2, tmpev, area);
    tmpnode = node1;
    node1 = node2;
    node2 = tmpnode;
    return true;
}


