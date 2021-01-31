#ifndef VECTOR_H
#define VECTOR_H
#include <memory>
#include <stdexcept>

template<typename T,typename A=std::allocator<T>>
class Vector
{
    public:
        class iterator : public std::iterator<T,std::random_access_iterator_tag> {
        private:
            T *value;
        public:
            iterator(T *v) {value=v;}
            iterator& operator++() {++value;return *this;}
            iterator& operator++(int) {++value;return *this;}
            iterator& operator--(int) {--value;return *this;}
            iterator& operator--() {--value;return *this;}
            iterator operator+(const int& n) {value+=n;return *this;}
            iterator operator-(const int& n) {value-=n;return *this;}
            iterator& operator+=(const int& n) {value+=n;return *this;}
            iterator& operator-=(const int& n) {value-=n;return *this;}
            bool operator!=(const iterator& r) {return value!=r.value;}
            bool operator==(const iterator& r) {return value==r.value;}
            bool operator<(const iterator& r) {return value<r.value;}
            bool operator>(const iterator& r) {return value>r.value;}
            T& operator*() {return *value;}
        };
        iterator begin() {return iterator(elems); }
        iterator end() {return iterator((elems+sz));}
        Vector& operator=(const Vector &other);
        void reserve(unsigned int newspace);
        void resize(unsigned int newsize);
        unsigned int capacity() const {return space;}
        unsigned int size() const {return sz;}
        void push_back(const T &element);
        Vector(const Vector &v);
        T& at(int n);
        T& operator[](int i) {return elems[i];}
        bool empty() {return sz==0;}
        T& back() {return elems[sz-1];}
        T& front() {return elems[0];}
        T* data() {return &front();}
        void pop_back();
        Vector() {sz=space=0;elems=nullptr;}
        ~Vector() {alloc.deallocate(elems,space);}
        explicit Vector(int n) { sz=space=static_cast<unsigned int>(n);elems = alloc.allocate(space); for(unsigned int i=0;i<sz;++i) alloc.construct(&elems[i]);}
        explicit Vector(int n,const T& val);
        void insert(iterator pos,const T& val);
        void erase(iterator pos);
        void erase(iterator f,iterator l);
        void clear();
        void swap(Vector &other);
    private:
        A alloc;
        T *elems;
        unsigned int sz,space;

};

template<typename T,typename A>
T& Vector<T,A>::at(int n)
{
    if(n>=static_cast<int>(sz)||n<0) {
        throw std::out_of_range("Error range!\n");
    }
    return elems[n];
}




template<typename T,typename A>
Vector<T,A>::Vector(const Vector &v)
{
    sz=v.sz;
    space=v.space;
    if(elems!=nullptr) {
        alloc.deallocate(elems,space);
    }
    elems = v.elems;
}

template<typename T,typename A>
void Vector<T,A>::reserve(unsigned int newspace)
{
    if(newspace<=space) return;
    T *newelems = alloc.allocate(newspace);
    for(unsigned int i=0;i<sz;++i) alloc.construct(&newelems[i],elems[i]);
    for(unsigned int i=0;i<sz;++i) alloc.destroy(&elems[i]);
    alloc.deallocate(elems,space);
    space=newspace;
    elems=newelems;
}


template<typename T,typename A>
void Vector<T,A>::resize(unsigned int newsize)
{
    if(newsize==sz) {
        return;
    }
    else if(newsize>sz) {
        reserve(newsize);
        for(unsigned int i=sz;i<newsize;++i) alloc.construct(&elems[i]);
    }
    else {
        T *p = alloc.allocate(space);
        for(unsigned int i=0;i<newsize;++i) alloc.construct(&p[i],elems[i]);
        alloc.deallocate(elems,space);
        elems=p;
    }
    sz=newsize;
}

template<typename T,typename A>
void Vector<T,A>::push_back(const T& element)
{
    if(sz==space||space==0) {
        reserve(space+8);
    }
    alloc.construct(&elems[sz],element);
    ++sz;
}

template<typename T,typename A>
void Vector<T,A>::pop_back()
{
    resize(sz-1);
}

template<typename T,typename A>
Vector<T,A>& Vector<T,A>::operator=(const Vector &other)
{
    reserve(other.space);
    resize(0);
    for(unsigned int i=0;i<other.size();++i) alloc.construct(&elems[i],other.elems[i]);
    sz=other.sz;
    space=other.space;
    return *this;
}

template<typename T,typename A>
Vector<T,A>::Vector(int n,const T& val)
{
    sz=space=static_cast<unsigned int>(n);
    elems = alloc.allocate(sz);
    for(unsigned int i=0;i<sz;++i) alloc.construct(&elems[i],val);
}


template<typename T,typename A>
void Vector<T,A>::insert(iterator pos,const T& val)
{
    if(sz==space) reserve(space+1);
    T buf = *pos;
    *pos = val;
    ++pos;
    for(;pos!=end();++pos) {
        T b = *pos;
        *pos = buf;
        buf = b;
    }
    elems[sz] = buf;
    ++sz;
}

template<typename T,typename A>
void Vector<T,A>::erase(iterator pos)
{
    if(pos<begin()||pos>end()) {
        throw std::out_of_range("Error iterator range!\n");
    }
    for(;pos!=end();++pos) {
        *pos = *(pos+1);
        --pos;
    }
    alloc.destroy(&elems[sz-1]);
    --sz;
}

template<typename T,typename A>
void Vector<T,A>::clear()
{
    alloc.deallocate(elems,space);
    elems=nullptr;
    sz=space=0;
}

template<typename T,typename A>
void Vector<T,A>::swap(Vector &other)
{
    Vector<T> buff = other;
    other.clear();
    other = *this;
    this->clear();
    *this = buff;
}

#endif // VECTOR_H
