#include <iostream>
#include "btree.h"
using namespace std;
int main()
{
    BTree bt(3);
    bt.insert(1,1);
    bt.insert(2,2);
    bt.insert(3,3);
    bt.insert(4,4);
    bt.insert(5,5);
    bt.insert(6,6);
    bt.insert(7,7);
    bt.insert(8,8);
    bt.insert(9,9);
    bt.insert(10,10);
    bt.insert(11,11);
    bt.insert(12,12);
    bt.insert(13,13);
    bt.insert(14,14);
    bt.insert(15,15);
    bt.insert(16,16);
    bt.del(11);
    bt.visit();
    cout << "Great!!!" << endl;
}