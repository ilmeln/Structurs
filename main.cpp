#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Vector.h"
#include "Tree.h"
using namespace std;


int main()
{

    return 0;
}

void test_vector()
{
    Vector<int> vec;
    for(int i=2;i<11;++i) {
        vec.push_back(i*i);
    }
    cout << "Size: " << vec.size() << endl;
    for(auto it = vec.begin(); it!=vec.end();++it) {
        cout << *it<<endl;
    }
    vec.erase(vec.begin()+4);
    cout << "------------------\nSize: " << vec.size()<<endl;
    for(auto it = vec.begin(); it!=vec.end();++it) {
        cout << *it<<endl;
    }
}
