#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <memory> //shared_ptr
#include <random>
#include <chrono>
#include <iostream>

/**
 * 缺陷:
 * @ 选择层数哪里局限性太高 数据大了很难得到最优的结构
 * @ 对于数据要求太高 1.可拷贝2.重载小于号和等于号3
*/

template<typename Type>
class SkipList{
private:
    struct Node{
        Type value; //存储的值
        uint32_t level; //跨越几层
        std::shared_ptr<Node[]> next = nullptr; //指向下一个节点

        Node(Type vl, uint32_t le) :
            value(vl) , level(le), next(new Node[le]){}

        Node() = default;    
    };

    static constexpr const uint32_t maxlevel = 32;
    Node head = Node(Type(), maxlevel); //初始化
    uint32_t size = 0; //当前节点个数
    uint32_t levelcount = 1;

    int GetLevel() const {
        unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
        mt19937 generator(seed1); //梅森旋转法
        int level = 1;
        while(true){
            int t = generator()%2;
            if(t&1){
                ++level;
            }else{
                break;
            }
        }
        return level;
    }

public:
    SkipList() = default;

    Node find(Type value) const{
        Node Temp = head; //可拷贝
        for(int i = levelcount - 1; i >= 0; --i){   //重载小于号
            while(Temp.next[i].next != nullptr && Temp.next[i].value < value){
                Temp = Temp.next[i];
            }
        }
        if(Temp.next != nullptr && Temp.next[0].value == value){
            std::cout << "find!\n";
            return Temp.next[0];
        } else {
            return Node();
        }
    }

    void insert(Type value){
        int level = GetLevel();
        Node* newNode = new Node(Type(value), level); //泄露 修改结构
        Node update[level];

        Node Temp = head;

        for(int i = level - 1; i >= 0; --i){
            while(Temp.next[i].next != nullptr && Temp.next[i].value < value){
                Temp = Temp.next[i];
            }
            update[i] = Temp;
        }

        for(int i = 0; i < level; ++i){
            newNode->next[i] = update[i].next[i];
            update[i].next[i] = *newNode;
        }

        if(level > levelcount)
            levelcount =  level;

        ++size;
    }

    void Delete(Type value){
        Node update[levelcount];
        Node Temp = head;

/*         for(int i = levelcount - 1; i >= 0; --i){
            while(Temp.next != nullptr && Temp.next[i].next != nullptr && Temp.next[i].value < value){
                Temp = Temp.next[i];
            }
            update[i] = Temp;
        } */

        for(int i = levelcount - 1; i >= 0; --i){
            while(Temp.next[i].next != nullptr && Temp.next[i].value < value){
                Temp = Temp.next[i];
            }
            update[i] = Temp;
        }
        
        if(Temp.next[0].next != nullptr && Temp.next[0].value == value){//重载等于号
            --size;
            for(int i = levelcount - 1; i >= 0; --i){
                if(update[i].next[i].next != nullptr && update[i].next[i].value == value){
                    update[i].next[i] = update[i].next[i].next[i];
                }
            }
            std::cout << "删除成功\n";
        }
    }

    void show() const {
        Node Temp = head;
        while(Temp.next[0].next != nullptr){
            std::cout << Temp.next[0].value << " ";
            Temp = Temp.next[0];
        }
        putchar('\n');
    }
};

#endif //SKIPLIST_H_