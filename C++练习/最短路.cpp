#include<queue>
#include<iterator>
#include<vector>
#include<bits/stdc++.h>
#include<iostream>
#include<memory>
using std::cout;
using std::endl;
#define MAX 200

typedef struct {
    char name[10];
    char introduction[20];
    int tag;
}Vertex;

typedef struct {
    Vertex vex[MAX];
    int edge[MAX][MAX];
    int vexnum;
    int edgenum;
}Graph;
int end;
int vis[200];
std::stack<int> sta;
std::vector<std::stack<int> > PathData;

void Dfs(std::shared_ptr<Graph> G, int start) {
    if (start == end) {
        PathData.push_back(sta);
        return;
    }
    for (int i = 1;i <= G->vexnum;++i) {
        if (0 == vis[i] && G->edge[start][i]>0) {
            vis[i] = 1;
            sta.push(start);
            Dfs(G, i);
            vis[i] = 0;
            sta.pop();
        }
    }
}

std::shared_ptr<Graph> ReturnGraph(){
    static auto singleton = std::make_shared<Graph>();
    return singleton;
}

void GraphInit(int End, int NumVex){
    auto g = ReturnGraph();
    PathData.clear();
    g->vexnum = NumVex;
    end = End;
    memset(g->edge, -1, sizeof(g->edge));
    memset(vis, 0, sizeof(vis));
    g->edge[1][2] = 1;
    g->edge[1][3] = 12;
    g->edge[2][3] = 9;
    g->edge[2][4] = 3;
    g->edge[3][5] = 5;
    g->edge[4][3] = 4;
    g->edge[4][5] = 13;
    g->edge[4][6] = 15;
    g->edge[6][7] = 4;
    g->edge[7][8] = 4;
    g->edge[8][9] = 4;
    g->edge[9][10] = 4;

    for (int i = 0;i <= 12;++i) g->edge[i][i] = 0;

    g->edge[2][1] = 1;
    g->edge[3][1] = 12;
    g->edge[3][2] = 9;
    g->edge[4][2] = 3;
    g->edge[5][3] = 5;
    g->edge[3][4] = 4;
    g->edge[5][4] = 13;
    g->edge[6][4] = 15;
    g->edge[7][6] = 4;
    g->edge[8][7] = 4;
    g->edge[9][8] = 4;
    g->edge[10][9] = 4;
}

decltype(PathData) Running(int start){
    auto g = ReturnGraph();
    vis[start] = 1;
    Dfs(g, start);
    return PathData;
}

void show(decltype(PathData) Data){
    std::cout << "The number of paths is " << Data.size() << std::endl;
    for(auto T : Data) {
        while (T.size()) {
            std::cout << T.top() << " ";
            T.pop();
        }
        putchar('\n');
    }
}

void ShortestPath(decltype(PathData) Data){
    size_t length = 0x3f3f3f3f;
    size_t all = 0;
    for(auto T : Data){
        if(T.size() < length){
            length = T.size();
            all = 1;
        }else if(T.size() == length){
            ++all;
        }
    }
    std::cout << "shortest path is total of " << all << ".\n";
    for(auto T : Data){
        if(length == T.size()){
            while (T.size()) {
                std::cout << T.top() << " ";
                T.pop();
            }
            putchar('\n');
        }
    }

}

int main(){
    /**
     * @ GraphInit parameters:
     * 1> end : position.
     * 2> num : the total number of nodes.
     * @ Running parameter is start position.
    */
    GraphInit(5, 10);
    show(Running(1));
    
    GraphInit(5, 10);
    ShortestPath(Running(1));
    return 0;
}