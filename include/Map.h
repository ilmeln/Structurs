#ifndef MAP_H
#define MAP_H
#include <iostream>


struct node {
    int value;
    node *left,*right,*parent;
    node() {value=0;left=right=parent=nullptr;}
};


class Tree {
private:
    node *root;
    void inOrder(node *x);
    void postOrder(node *x);
    void cut(node *x,node *r);
    node *next(node *x);
    node *minN( node *n);
public:
    Tree() {root=nullptr;}
    void insert(const int& k);
    void erase(const int& k);
    void show();
};


void Tree::insert(const int& k)
{
    if(root==nullptr) {
        root = new node;
        root->value = k;
        return;
    }
    node *r = root;
    while(true) {
        if(root->value==k) {
            root = r;
            return;
        }
        else if(root->value<k) {
            if(root->right==nullptr) {
                node *n = new node;
                n->value = k;
                n->parent = root;
                root->right=n;
                root = r;
                return;
            }
            root=root->right;
        }
        else {
            if(root->left==nullptr) {
                node *n=new node;
                n->value=k;
                n->parent=root;
                root->left = n;
                root = r;
                return;
            }
            root = root->left;
        }

    }
}

void Tree::inOrder(node *x)
{
    if(x!=nullptr) {
        inOrder(x->left);
        std::cout<<x->value<<std::endl;
        inOrder(x->right);
    }
}

void Tree::show()
{
    inOrder(root);
}

node* Tree::minN( node *n)
{
    while(n->left!=nullptr) {
        n=n->left;
    }
    return n;
}


node* Tree::next(node *x)
{
    if(x->right!=nullptr) {
        return minN(x->right);
    }
    node *y=x->parent;
    while(y!=nullptr&&x==y->right) {
        x=y;
        y=y->parent;
    }
    return y;
}


void Tree::erase(const int& k)
{
    node *r = root;
    while(true) {
        if(root->value==k) {
            cut(root,r);
            return;
        }
        else if(root->value<k) {
            if(root->right==nullptr) {
                root=r;
                return;
            }
            root=root->right;
        }
        else {
            if(root->left==nullptr) {
                root=r;
                return;
            }
            root=root->left;
        }
    }
}



void Tree::cut(node *x,node *r)
{
    node *y;
    if(x->right==nullptr||x->left==nullptr) {
        y = x->left;
    }
    else {
        y= next(x);
    }
    node *z = x->right;
    if(y==nullptr) {
        if(x->parent->right==x) {
            x->parent->right = z;
        }
        else {
            x->parent->left = z;
        }
        if(z!=nullptr) {
            z->parent = x->parent;
        }
        delete x;
        root = r;
    }
    else {
        if(z==nullptr) {
            if(x->parent->right==x) {
                x->parent->right =y;
            }
            else {
                x->parent->left= y;
            }
            y->parent = x->parent;
            delete x;
            root = r;
        }
        else {
            int num = x->value;
            x->value = y->value;
            y->value = num;
            cut(y,r);
        }
    }
}



#endif // MAP_H
