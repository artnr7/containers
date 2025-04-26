#include "s21_list.h"
#include <list>
#include <iostream>


int main(){

    list<int> l1 = {6,2,2,7};

    list<int> l2 = {3,5,8};
    list<int> l3 = {2,3,4,5};

    l2.merge(l3);
    l2.sort();
    // l1.unique();
    for (auto i = l2.begin(); i != l2.end(); i++)
    {
        std::cout<< *i<< " ";
    }
    for (auto i = l3.begin(); i != l3.end(); i++)
    {
        std::cout<< *i<< " ";
    }
    
    
    return 0;
}

// {5,4,67,8};
//           ^
// {5,8,7};
//        ^

// {5, 4, 5, 8, 7, 67, 8}