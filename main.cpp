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

    void check(node *i) {

        if (i== nullptr){
            return;
        }

        if (i==root){
            if (i->color==false){
                i->color=true;
            }
            return;
        }

        node *p=i->parent;
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
                //如果父亲是红色，叔叔节点不存在或为黑节点，并且插入节点的父亲节点是祖父节点的左子节点
                if ((uncle== nullptr||uncle->color== true)&&grandFa->left==p){
                    if (p->left==i){
                        //插入节点是其父节点的左子节点
                        p->color= true;
                        grandFa->color=false;
                        p=RR(grandFa);
                        check(p);
                    } else {
                        //插入节点是其父节点的右子节点
                        LL(p);
                        i->color=true;
                        grandFa->color=false;
                        i=RR(grandFa);
                        check(i);
                    }
                } else if ((uncle== nullptr||uncle->color== true)&&grandFa->right==p){
                    //叔叔节点不存在或为黑节点，并且插入节点的父亲节点是祖父节点的右子节点
                    if (p->right==i){
                        //插入节点是其父节点的右子节点
                        p->color= true;
                        grandFa->color=false;
                        p=LL(grandFa);
                        check(p);
                    } else{
                        //插入节点是其父节点的右子节点
                        RR(p);
                        i->color=true;
                        grandFa->color=false;
                        i=LL(grandFa);
                        check(i);
                    }
                }
            }
        }


    }



    //左旋
    node *LL(node *p){
        node *right=p->right;

        //   让 right 的左子树 成为 p 的右子树
        p->right= right->left;
        if (right->left!= nullptr){
            right->left->parent=p;
        }

        // 让 p 成为 right 的左子树
        if (p==root){
            root=right;
            right->parent= nullptr;
        } else{
            if (p->parent->left==p){
                p->parent->left=right;
            } else{
                p->parent->right=right;
            }
            right->parent=p->parent;
        }

        right->left=p;
        p->parent=right;


        return right;
    }

    //右旋
    node *RR(node *p){
        node *left=p->left;

        //  让 left 的右子树 成为 p 的左子树
        p->left=left->right;
        if (left->right!= nullptr){
            left->right->parent=p;
        }

        //        让 p 成为 left 的右子树
        if (p== root){
            root=left;
            left->parent= nullptr;
        } else{
            if (p->parent->left==p){
                p->parent->left=left;
            } else{
                p->parent->right=left;
            }
            left->parent=p->parent;
        }

        left->right=p;
        p->parent=left;


        return left;
    }


    //旋转，变色的操作
    void afterDelete(node *parent,node *brother){
        //兄弟在右边
        if (parent->right==brother){
            //兄弟为黑色
            if (brother->color== true){
                if (brother->right!= nullptr&&brother->right->color== false){
                    //兄弟节点相同方向有一个红色子节点
                    brother->color=parent->color;
                    parent=LL(parent);
                    parent->left->color= true;
                    parent->right->color= true;

                } else if (brother->left!= nullptr&&brother->left->color== false){
                    //兄弟节点不同方向有一个红色子节点
                    brother=RR(brother);
                    brother->color=parent->color;
                    parent=LL(parent);
                    parent->left->color= true;
                    parent->right->color= true;

                } else{
                    //兄弟节点没有红色子节点
                    brother->color=false;

                    if (parent->color== false){
                        parent->color=true;
                    } else{
                        node *pp=parent->parent;
                        if (pp== nullptr){
                            return;
                        }
                        node *pb;
                        if (pp->left==parent){
                            pb=pp->right;
                        } else{
                            pb=pp->left;
                        }
                        afterDelete(pp,pb);
                    }
                }
            } else{
                //兄弟为红色时
                brother->color= true;
                parent->color=false;
                LL(parent);
            }
        } else{
            //兄弟在左边,为黑色
            if (brother->color== true){
                if (brother->left!= nullptr&&brother->left->color== false){
                    //兄弟节点相同方向有一个红色子节点
                    brother->color=parent->color;
                    parent=RR(parent);
                    parent->left->color= true;
                    parent->right->color= true;

                } else if (brother->right!= nullptr&&brother->right->color== false){
                    //兄弟节点不同方向有一个红色子节点
                    brother=LL(brother);
                    brother->color=parent->color;
                    parent=RR(parent);
                    parent->left->color= true;
                    parent->right->color= true;

                } else{
                    //兄弟节点没有红色子节点
                    brother->color=false;

                    if (parent->color== false){
                        parent->color=true;
                    } else{
                        node *pp=parent->parent;
                        if (pp== nullptr){
                            return;
                        }
                        node *pb;
                        if (pp->left==parent){
                            pb=pp->right;
                        } else{
                            pb=pp->left;
                        }
                        afterDelete(pp,pb);
                    }
                }
            } else{
                //兄弟为红色时
                brother->color= true;
                parent->color=false;
                RR(parent);
            }
        }

    }


    bool Delete(node *p){

        //被删结点有两个子结点，且被删结点为黑色或红色
        if (p->left!= nullptr&&p->right!= nullptr){

            node *s=p->left;
            while (s->right!= nullptr){
                s=s->right;
            }
            p->data=s->data;
            return Delete(s);
        }

        //删除节点为根节点，且只有一个子节点
        if (p==root){
            if (p->left!= nullptr){
                root=p->left;
            } else if (p->right!= nullptr){
                root=p->right;
            } else{
                root= nullptr;
            }
            return true;
        }

        node *parent=p->parent;

        //被删节点无子节点，且被删结点为红色
        if (p->color== false&&p->left== nullptr&&p->right== nullptr){
            if (parent->left==p){
                parent->left= nullptr;
            } else{
                parent->right= nullptr;
            }
            delete p;
            return true;
        }



        //节点为黑色
        if (p->color== true){
            if (p->left== nullptr&&p->right== nullptr){
                //被删结点无子结点，且被删结点为黑色

                if (parent->left== p){

                    parent->left= nullptr;
                    delete p;
                    if (parent->right== nullptr){
                        cout<<"错误"<<endl;
                        return false;
                    }

                    node *brother=parent->right;
                    afterDelete(parent,brother);
                } else{
                    parent->right= nullptr;
                    delete p;

                    if (parent->left== nullptr){
                        cout<<"错误"<<endl;
                        return false;
                    }

                    node *brother=parent->left;
                    afterDelete(parent,brother);

                }
            } else {
                //被删结点有一个子结点，且被删结点为黑色,这种组合下，被删结点node的另一个子结点value必然为红色
                if (p->left!= nullptr){
                    if (parent->left==p){
                        parent->left=p->left;
                    } else{
                        parent->right=p->left;
                    }
                    p->left->parent=parent;
                    p->left->color=true;
                } else{
                    if (parent->left==p){
                        parent->left=p->right;
                    } else{
                        parent->right=p->right;
                    }
                    p->right->parent=parent;
                    p->right->color=true;
                }
                delete p;
                return true;
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


    bool deleteNode(int data){
        node *p=root;
        while (p!= nullptr){
            if (p->data>data){
                p=p->left;
            } else if (p->data<data){
                p=p->right;
            } else{
                break;
            }
        }
        if (p== nullptr){
            cout<<"未找到"<<endl;
            return false;
        }

        Delete(p);
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
                        check(s);
                        return true;
                    }
                } else{
                    if (head->right!= nullptr)
                    {
                        head = head->right;
                    } else{
                        head->right=s;
                        s->parent=head;
                        check(s);
                        return true;
                    }
                }
            }
        }
        return false;
    }

};

int main() {
    RB_Tree<int> s;
    s.insert(6);
    s.insert(4);
    s.insert(8);
    s.insert(2);
    s.insert(5);
    s.insert(1);
    s.insert(7);
    s.insert(0);
    s.deleteNode(4);
    s.showTree();
}
