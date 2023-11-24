#include <iostream>
#include "List.hpp"
#include <list>
int main(void)
{
    List<int> l(1);
    std::list<int> q;
    auto it = l.begin();
    std::cout << *it << std::endl;
    return 0;
}