#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

using namespace std;
void makeGraph(bool**& graph, int n)
{
    graph = new bool*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new bool[n];
    }
    for (int i = 0; i < n; i++) {
        graph[i][i] = 1;
        for (int j = i + 1; j < n; j++) {
            graph[i][j] = (rand() > (RAND_MAX / 2));
            graph[j][i] = graph[i][j];
        }
    }
}
void printGraph(bool** graph, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}
void do_check1(bool** graph, int n, bool* vis, int now)
{
    if (vis[now]) {
        return;
    }
    vis[now] = true;
    for (int i = 0; i < n; i++) {
        if (graph[now][i]) {
            do_check1(graph, n, vis, i);
        }
    }
}
bool check1(bool** graph, int n)
{ //连通性检查
    bool* vis = new bool[n];
    memset(vis, 0, sizeof(bool[n]));
    do_check1(graph, n, vis, 0);
    for (int i = 0; i < n; i++) {
        if (vis[i] != true) {
            return false;
        }
    }
    return true;
}

struct stack {
    int top, node[100];
} s;

void DFS(bool** graph, int n, int x)
{
    s.top++;
    s.node[s.top] = x;
    for (int i = 0; i < n; i++) {
        if (graph[i][x] > 0) {
            graph[i][x] = 0;
            graph[x][i] = 0;
            DFS(graph, n, i);
            break;
        }
    }
}

void Fleury(bool** graph, int n, int* ans, int& cnt, int x)
{
    int b;
    s.top = 0;
    s.node[s.top] = x;
    while (s.top >= 0) {
        b = 0;
        for (int i = 0; i < n; i++) {
            if (graph[s.node[s.top]][i] > 0) {
                b = 1;
                break;
            }
        }
        if (b == 0) {
            ans[cnt++] = s.node[s.top] + 1;
            s.top--;
        } else {
            s.top--;
            DFS(graph, n, s.node[s.top + 1]);
        }
    }
    cout << endl;
}

void answer(int* ans, int cnt)
{
    for (int i = 0; i < cnt; i++)
        cout << ans[i] << " ";
    cout << endl;
}

int main()
{
    int n;
    srand(time(0));
    cout << "请输入节点数" << endl;
    cin >> n;
    bool** graph = nullptr;
    makeGraph(graph, n);
    cout << "生成的矩阵为" << endl;
    printGraph(graph, n);

    if (check1(graph, n)) {
        cout << "非连通图" << endl;
        return 0;
    }

    int start, num = 0;
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++)
            degree += graph[i][j];
        if (degree % 2) {
            start = i;
            num++;
        }
    }

    if (num == 0 || num == 2) {
        int* ans = new int[n];
        int cnt;
        Fleury(graph, n, ans, cnt, start);
        if (ans[0] == ans[n - 1])
            cout << "该图为欧拉图，欧拉回路为: ";
        else
            cout << "该图为半欧拉图，欧拉路为: ";
        answer(ans, cnt);
    } else
        cout << "非欧拉图或半欧拉图" << endl;  
    return 0; 


    return 0;
}