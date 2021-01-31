#ifndef BILIST_H
#define BILIST_H
#include <memory>

template<typename T,typename A = std::allocator<T>>
struct Binode {
    T data;
    A alloc;
    Binode *prev,*next;
    Binode() {prev=next=nullptr;alloc.construct(&data);}
    ~Binode() {prev=next=nullptr;alloc.destroy(&data);}
    Binode& operator=(const Binode& b) {prev=b.prev;next=b.next;alloc.construct(&data,b.data);}
    Binode(const Binode& b) {prev=b.prev;next=b.next;alloc.construct(&data,b.data);}
};


template<typename T,typename A = std::allocator<T>>
class Bilist
{
    public:
        Bilist() {tail=head=nullptr;sz=0;}
        ~Bilist();
        class iterator : public std::iterator<Binode<T>,std::bidirectional_iterator_tag> {
        private:
            Binode<T> *val;
        public:
            iterator(Binode<T> *v) {val=v;}
            iterator& operator++() {val=val->next;return *this;}
            iterator& operator--() {val=val->prev;return *this;}
            iterator& operator++(int) {val=val->next;return *this;}
            iterator& operator--(int) {val=val->prev;return *this;}
            bool operator==(const iterator& o) {return val==o.val;}
            bool operator!=(const iterator& o) {return val!=o.val;}
            T& operator*() {return val->data;}
        };
        void push_back(const T& v);
        void push_front(const T& v);
        iterator begin() {return iterator(head);}
        iterator end() {return iterator(tail);}
        bool empty() {return head==nullptr||tail==nullptr;}
        unsigned int size() {return sz;}
    private:
        Binode<T> *tail,*head;
        unsigned int sz;
        A alloc;

};

template<typename T,typename A>
Bilist<T,A>::~Bilist()
{
    while(head!=tail) {
        Binode<T> *n = head->next;
        delete head;
        head=n;
    }
    delete tail;
}



template<typename T,typename A>
void Bilist<T,A>::push_back(const T& v)
{
    if(head==nullptr||tail==nullptr) {
        tail = new Binode<T>;
        head = new Binode<T>;
        tail->prev = head;
        head->next = tail;
        alloc.construct(&head->data,v);
        ++sz;
        return;
    }
    Binode<T> *n = new Binode<T>;
    alloc.construct(&tail->data,v);
    tail->next = n;
    n->prev = tail;
    tail = n;
    ++sz;
}

template<typename T,typename A>
void Bilist<T,A>::push_front(const T& v)
{
    if(head==nullptr||tail==nullptr) {
        tail = new Binode<T>;
        head = new Binode<T>;
        tail->prev = head;
        head->next = tail;
        alloc.construct(&head->data,v);
        ++sz;
        return;
    }
    Binode<T> *n = new Binode<T>;
    alloc.construct(&n->data,v);
    head->prev = n;
    n->next = head;
    head = n;
    ++sz;
}

#endif // BILIST_H
