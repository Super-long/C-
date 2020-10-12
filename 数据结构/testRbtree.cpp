#include <iostream>
#include "RBtree.h"
using namespace std;

int main(){
    int a[]= {10, 40, 30, 60, 90, 70, 20, 50, 80};
    int check_insert=1;    // "插入"动作的检测开关(0，关闭；1，打开)
    int check_remove=0;    // "删除"动作的检测开关(0，关闭；1，打开)
    int i;
    int ilen = (sizeof(a)) / (sizeof(a[0])) ;
    RBTree<int>* tree=new RBTree<int>();
 
    cout << "== 原始数据: ";
    for(i=0; i<ilen; i++)
        cout << a[i] <<" ";
    cout << endl;

    for(i=0; i<ilen; i++) {
        tree->insert(a[i]);
        // 设置check_insert=1,测试"添加函数"
        if(check_insert){
            cout << "== 添加节点: " << a[i] << endl;
            cout << "== 树的详细信息: " << endl;
            cout << endl;
        }
    }
    tree->print();

    cout << "开始删除\n";
    for(i=0; i<ilen/2;++i){
        tree->remove(a[i]);
    }
    tree->print();
    return 0;
}