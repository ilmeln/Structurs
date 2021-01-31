#ifndef LIST_H
#define LIST_H
#include <memory>
#include <stdexcept>
#include <iostream>

template<typename T>
struct Node {
    T value;
    Node *next;
    Node() {next=nullptr;}
    Node(Node *n,T val) {next=n;value=val;}
    Node& operator=(const Node& o) {next=o.next;value=o.value;return *this;}
    Node(const Node& o) {next=o.next;value=o.value;}

};







template<typename T>
class List
{
    public:
        class iterator : public std::iterator<Node<T>,std::forward_iterator_tag> {
        private:
            Node<T> *val;
        public:
            iterator& operator++(){val=val->next;return *this;}
            iterator& operator++(int) {val=val->next;return *this;}
            bool operator==(const iterator &o) {return val=o.val;}
            bool operator!=(const iterator &o) {return val!=o.val;}
            T& operator*() {return val->value;}
            Node<T>* operator->() {return val;}
            iterator(Node<T> *e) {val=e;}
        };
        List();
        ~List();
        void push_back(const T& v);
        iterator begin() const {return iterator(head);}
        iterator end() const {return iterator(nullptr);}
        void erase(const T& v);
        void reverse();
        void clear();
        void pop_front();
        void pop_back() {if(head==nullptr){return;}Node<T> *n = head->next;delete head;head = n;}
        List(T* first,T* last);
        bool empty() const {return head==nullptr;}
        void sort();
        template<typename Comp>
        void sort(Comp cmp);
        void unique();
        void resize(int sz);
        T& front() {return head->value;}
    private:
        bool cmp(const T& l,const T& r) const {return l<=r;}
        Node<T> *head;
        void help_reverse(Node<T> *prev,Node<T> *curr);
        bool is_sort;
};



template<typename T>
List<T>::List()
{
    head=nullptr;
    is_sort=false;
}


template<typename T>
List<T>::~List()
{
    while(head!=nullptr) {
        Node<T> *n = head->next;
        delete head;
        head = n;
    }
}


template<typename T>
void List<T>::push_back(const T& v)
{
    if(head==nullptr) {
        head = new Node<T>;
        head->value=v;
        return;
    }
    Node<T> *n= new Node<T>;
    n->next = head;
    n->value = v;
    head = n;
}


template<typename T>
void List<T>::erase(const T& v)
{
    if(head->value==v) {
        Node<T> *n = head->next;
        delete head;
        head = n;
        return;
    }
    Node<T> *n = head;
    while(true) {
        if(head->next==nullptr) {
            head=n;
            return;
        }
        else if(head->next->value==v) {
            Node<T> *m = head->next->next;
            delete head->next;
            head->next = m;
            head = n;
            return;
        }
        head=head->next;
    }
}


template<typename T>
void List<T>::reverse()
{
    if(head==nullptr||head->next==nullptr) return;
    help_reverse(head,head->next);
}


template<typename T>
void List<T>::help_reverse(Node<T> *prev,Node<T> *curr)
{
    if(prev==head) {
        head->next=nullptr;
    }
    if(curr==nullptr) {
        head = prev;
        return;
    }
    else if(curr->next==nullptr) {
        head=curr;
        head->next = prev;
        return;
    }
    help_reverse(curr,curr->next);
    curr->next = prev;
}

template<typename T>
void List<T>::clear()
{
    if(head==nullptr) return;
    while(head!=nullptr) {
        Node<T> *n = head->next;
        delete head;
        head = n;
    }
}





template<typename T>
List<T>::List(T* first,T* last)
{
    head = new Node<T>;
    head->next = nullptr;
    head->value = *first;
    ++first;
    for(;first!=last;++first) {
        Node<T> *n = new Node<T>;
        n->next = head;
        n->value = *first;
        head = n;
    }
}


template<typename T>
void List<T>::pop_front()
{
    if(head==nullptr) {
        return;
    }
    else if(head->next==nullptr) {
        delete head;
        head = nullptr;
    }
    Node<T> *m = head;
    while(true) {
        if(head->next->next==nullptr) {
            delete head->next;
            head->next=nullptr;
            head=m;
            return;
        }
        head=head->next;
    }
}

template<typename T>
template<typename Comp>
void List<T>::sort(Comp c)
{
    if(head==nullptr||head->next==nullptr) return;
    Node<T> *n = head;
    c=cmp;
    while(true) {
        if(head->next==nullptr) {
            head=n;
            is_sort=true;
            return;
        }
        if(!c(head->value,head->next->value)) {
            T el = head->value;
            head->value = head->next->value;
            head->next->value = el;
            head = n;
            continue;
        }
        head=head->next;
    }
}


template<typename T>
void List<T>::sort()
{
    if(head==nullptr||head->next==nullptr) return;
    Node<T> *n = head;
    while(true) {
        if(head->next==nullptr) {
            head=n;
            is_sort=true;
            return;
        }
        if(!cmp(head->value,head->next->value)) {
            T el = head->value;
            head->value = head->next->value;
            head->next->value = el;
            head= n;
            continue;
        }
        head=head->next;
    }
}

template<typename T>
void List<T>::unique()
{
    if(head==nullptr) return;
    Node<T> *n = head;
    if(is_sort) {
        while(true) {
            if(head->next==nullptr) {
                head=n;
                return;
            }
            else if(head->next->value==head->value) {
                Node<T> *t = head->next->next;
                delete head->next;
                head->next = t;
                continue;
            }
            head=head->next;
        }
    }
    while(true) {
        if(head->next==nullptr) {
            head=n;
            return;
        }
        Node<T> *c = head;
        head=head->next;
        while(head->next!=nullptr) {
            if(head->next->value==c->value) {
                Node<T> *z = head->next->next;
                delete head->next;
                head->next=z;
                continue;
            }
            head=head->next;
        }
        head=c->next;
    }
}


template<typename T>
void List<T>::resize(int sz)
{
    if(head==nullptr) return;
    int count=0;
    Node<T> *n = head;
    while(count!=(sz-1)&&head->next!=nullptr) {
        head=head->next;
        ++count;
    }
    if(count!=(sz-1)) {
        head = n;
        return;
    }
    while(head->next!=nullptr) {
        Node<T> *z = head->next->next;
        delete head->next;
        head->next=z;
    }
    head=n;
}

#endif // LIST_H
