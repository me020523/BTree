#include "btree.h"

//implementation of class InternalTreeNode-----------------------------
InternalTreeNode::InternalTreeNode(int order)
{
    this->order = order;
    this->keyCount = 0;
    this->childCount = 0;
    this->keys = new int[order - 1];
    this->child = new TreeNode*[order];
    
    for(int i = 0; i < order; i++)
	    this->child[i] = (TreeNode*)NULL;
    for(int i = 0; i < order - 1; i++)
	    this->keys[i] = -1;
}
InternalTreeNode::~InternalTreeNode()
{
    this->order = 0;
    this->keyCount = 0;
    if(this->keys)
        delete[] this->keys;
    if(this->child)
        delete[] this->child;
}
int InternalTreeNode::search(int key)
{
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
        if(keys[i] > key)
    	    break;
    }
    return child[i]->search(key);
}

TreeNode* InternalTreeNode::insert(int key, int value)
{
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
        if(keys[i] == true)
            return NULL;
        if(keys[i] > key)
            break;
    }
    TreeNode* tmp = child[i]->insert(key,value);
    
    if(tmp == this)
	return this;
    
    if(childCount < order)
    {
	//结点未满
	this->addChild(i + 1,tmp);
	return this;
    }
    
    //结点已满,当前结点分裂
    int half = (order >> 1);
    if(order % 2)
	half = half + 1;
    int cut_point = half;
    if((i + 1) < half)
	--cut_point;
    TreeNode* tmp_2 = split(cut_point);
    if(cut_point < half)
	addChild(i + 1,tmp);
    else
	addChild((i + 1) - cut_point,tmp);
    return tmp_2;
}
void InternalTreeNode::addChild(int p,TreeNode* t)
{
    int min = t->getMinKey();
    
    for(int j = keyCount - 1; j >= p - 1 ; j--)
    {
	keys[j + 1] = keys[j];
    }
    for(int j = childCount - 1; j >= p; j--)
    {
	child[j + 1] = child[j];
    }
    keys[p - 1] = min;
    child[p] = t;
    ++childCount;
    ++keyCount;
}
/**
 * 删除子结点
 */
void InternalTreeNode::delChild(TreeNode* t)
{

}

/**
 * 在位置p处分割结点
 * */
TreeNode* InternalTreeNode::split(int p)
{
    InternalTreeNode* q = new InternalTreeNode(order);
    int cc = childCount;
    int kc = keyCount;
    for(int i = p; i < cc; i++)
    {
	q->child[q->childCount++] = child[i];
	child[i] = NULL;
	--childCount;
	
	if(i < kc)
	{
	    q->keys[q->keyCount++] = keys[i];
	    keys[i] = 0;
	    --keyCount;
	}
    }
    keys[p - 1] = 0;
    return q;
}
/**
 * 返回子树的最小键值
 * 
 */
int InternalTreeNode::getMinKey()
{
    if(isLeaf())
	return keys[0];
    else
	return child[0]->getMinKey();
}
/**
 * 返回子树的最大键值
 * 
 */
int InternalTreeNode::getMaxKey()
{
    if(isLeaf())
	return keys[keyCount - 1];
    else
	return child[childCount - 1]->getMaxKey();
}
/**
 *遍历结点
 */
void InternalTreeNode::visit()
{

}
/**
 * 删除key
 */
bool InternalTreeNode::del(int key)
{
    return false;
}
////////////////////////////////////////////////////////////////////
//the implementation of class LeafTreeNode
LeafTreeNode::LeafTreeNode(int order)
{
    this->order = order;
    keys = new int[order - 1];
    keyCount = 0;
    for(int i = 0; i < order - 1;i++)
    {
        keys[i] = -1;
    }
    values = new int[order - 1];
    for(int i = 0; i < order - 1; i++)
    {
	values[i] = -1;
    }
}
LeafTreeNode::~LeafTreeNode()
{
    if(keys)
	delete[] keys;
    if(values)
	delete[] values;
}
int LeafTreeNode::search(int key)
{
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
        if(keys[i] == key)
	    return values[i];
        if(keys[i] > key)
	    return -1;
    }
    return -1;
}
TreeNode* LeafTreeNode::insert(int key,int value)
{
    int value = search(key);
    if(value >= 0)
	return this;  //the record already exists
    if(keyCount < (order - 1))
    {
	//the current leaf node is still not full
	int j = 0;
	for(j = 0;j < keyCount; j++)
	    if(keys[j] > key)
		break;
	for(int i = keyCount; i > j; i--)
	{
	    keys[i] = keys[i - 1];
	    values[i] = values[i - 1];
	}
	keys[j] = key;
	values[j] = value;
	
	return this;
    }
    
    //the current leaf node is full, a new leaf node must be created
    LeafTreeNode *p = new LeafTreeNode(order);
    p->keys[keyCount] = key;
    p->values[keyCount++] = value;
    
    return p;
}
bool LeafTreeNode::del(int key)
{
    return false;
}
void LeafTreeNode::visit()
{
    
}
int LeafTreeNode::getMaxKey()
{
    return keys[keyCount - 1];
}
int LeafTreeNode::getMinKey()
{
    return keys[keyCount - 1];
}
//////////////////////////////////////////////////////////////////////////////
//the implemetation of class BTree
BTree::BTree(int order)
{
    this->order = order;
    root = NULL;
}
BTree::~BTree()
{
    
}
bool BTree::search(int key)
{
    if(root)
    return root->search(key);
    return false;
}
bool BTree::insert(int key,int value)
{
    if(!root)
	root = new LeafTreeNode(order);
    
    if(!root->isFull())
	return root->insert(key,value);
    if(root->isLeaf())
    {
	InternalTreeNode *p = new InternalTreeNode(order);
	p->addChild(0,root);
	root = p;
	p = new LeafTreeNode(order);
	p->insert(key,value);
	root->addChild(1,p);
	return true;
    }
    else
    {
	InternalTreeNode *p = root->insert(key,value);
	if(p == root)
	    return true;
	else
	{
	    InternalTreeNode *q = new InternalTreeNode(order);
	    q->addChild(0,root);
	    q->addChild(1,p);
	    root = q;
	    return true;
	}
    }
    return false;
}
bool BTree::del(int key)
{
    return false;
}
void BTree::visit()
{
    
}
