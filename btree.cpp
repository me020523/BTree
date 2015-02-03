#include "btree.h"

//implementation of class InternalTreeNode
InternalTreeNode::InternalTreeNode(int order)
{
    this->order = order;
    this->keyCount = 0;
    this->childCount = 0;
    this->keys = new int[order - 1];
    this->child = new TreeNode[order];
    
    for(int i = 0; i < order; i++)
	this->child[i] = NULL;
    for(int i = 0; i < order - 1; i++)
	this->keys[i] = 0;
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
/**
 * 在结点中搜索key,若找到返回true,否则为false;
 * */
bool InternalTreeNode::search(int key)
{
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
	if(keys[i] == key)
	    return true;
	if(keys[i] > key)
	    break;
    }
    return child[i].search(key);
}
/**
 * 在结点中插入key，若成功则返回非NULL,否则为NULL;
 */
TreeNode InternalTreeNode::insert(int key)
{
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
	if(keys[i] == true)
	    return NULL;
	if(keys[i] > key)
	    break;
    }
    TreeNode tmp = child[i].insert(key);
    
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
    TreeNode tmp_2 = split(cut_point);
    if(cut_point < half)
	addChild(i + 1,tmp);
    else
	addChild((i + 1) - cut_point,tmp);
    return tmp_2;
}
void InternalTreeNode::addChild(int p,TreeNode t)
{
    int i = 0;
    int min = t.getMinKey();
    
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
 * 在位置p处分割结点
 * */
TreeNode InternalTreeNode::split(int p)
{
    InternalTreeNode * p = new InternalTreeNode(order);
    int cc = childCount;
    int kc = keyCount;
    for(int i = p; i < cc; i++)
    {
	p->child[p->childCount++] = child[i];
	child[i] = NULL;
	--childCount;
	
	if(i < kc)
	{
	    p->keys[p->keyCount++] = keys[i];
	    keys[i] = 0;
	    --keyCount;
	}
    }
    keys[p - 1] = 0;
    return p;
}
/**
 * 返回子树的最小值
 * 
 */
int InternalTreeNode::getMinKey()
{
    if(isLeaf())
	return keys[0];
    else
	return child[0].getMinKey();
}






