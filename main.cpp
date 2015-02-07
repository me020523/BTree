#include <iostream>
#include "btree.h"
using namespace std;
int main()
{
    BTree bt(5);
    bt.visit();
    cout << "Great!!!" << endl;
}