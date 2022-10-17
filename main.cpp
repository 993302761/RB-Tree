#include <iostream>
using namespace std;

/***
 * 红黑树的性质

    1.每个结点是红的或者黑的。
    2.根结点是黑的。
    3.每个叶子结点是黑的。
    4.如果一个结点是红的，则它的两个儿子都是黑的。
    5.对每个结点，从该结点到其子孙结点的所有路径上的包含相同数目的黑结点。
 */

template<class T>       //类模板

struct treeNode{
    struct treeNode *parent;
    struct treeNode *left;
    struct treeNode *right;
    bool color;      //  false为红色  true为黑色
    T data;
    treeNode(const T& x):
            left(nullptr),
            right(nullptr),
            parent(nullptr),
            color(false),
            data(x){}
};


template<class K>

class RB_Tree {

private:

    typedef treeNode<K> node;

    node *root;

    void freeNode(node *s){
        if (s== nullptr){
            return;
        }
        freeNode(s->left);
        freeNode(s->right);
        delete s;
    }

    int Height(node *p){
        if (p== nullptr){
            return 0;
        }
        int left=Height(p->left);
        int right=Height(p->right);
        return max(left,right)+1;
    }


    void show(node *n){
        if (n== nullptr)
            return;
        string color;
        if (n->color== false){
            color="red";
        } else{
            color="black";
        }
        cout<<"data: "<<n->data<<"  颜色: "<<color<<endl;
        show(n->left);
        show(n->right);
    }

    void check(node *p) {
        if (p== nullptr){
            return;
        }

        if(p->color== false){
            node *grandFa=p->parent;
            node *uncle= nullptr;
            if (grandFa->left==p){
                if (grandFa->right!= nullptr){
                    uncle=grandFa->right;
                }
            } else {
                if (grandFa->left != nullptr) {
                    uncle = grandFa->left;
                }
            }

            if (uncle!= nullptr&&uncle->color==false){
                //如果父亲是红色，叔叔是红色。
                p->color=true;
                uncle->color=true;
                grandFa->color= false;
                check(grandFa);
            } else{
                //如果父亲是红色，叔叔是黑色，且当前结点在父亲的父亲方向子树
                if ()
            }
        }


    }




public:

    RB_Tree():root(nullptr){}

    ~RB_Tree(){
        freeNode(root);
    };

    //获取高度
    int getHeight(){
        return Height(root);
    }

    node *getNode(int data){
        node *p=root;
        while (p!= nullptr){
            if (p->data==data){
                return p;
            } else if (p->data<data){
                p=p->right;
            } else{
                p=p->left;
            }
        }
        return nullptr;
    }




    //遍历
    void showTree(){
        show(root);
    }




    //插入节点
    bool insert(const K& data){
        if(root== nullptr)
        {
            root=new node(data);
            root->color= true;
        }
        else
        {
            node *head=root;
            node *s=new node(data);
            while (head!= nullptr)
            {
                if (s->data==head->data){
                    cout<<"节点 "<<data<<" 已存在"<<endl;
                    return false;
                }
                else if (s->data<head->data)
                {
                    if (head->left!= nullptr)
                    {
                        head= head->left;
                    } else{
                        head->left=s;
                        s->parent=head;

                        return true;
                    }
                } else{
                    if (head->right!= nullptr)
                    {
                        head = head->right;
                    } else{
                        head->right=s;
                        s->parent=head;
                        if (head->bf==1||head->bf==-1)
                        {
                            addBF(head);
                        }
                        return true;
                    }
                }
            }
        }
        return false;
    }

};

int main() {
    return 0;
}
