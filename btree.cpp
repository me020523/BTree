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
 * 删除key
 * 说明:本质是删除叶子结点中的键值对，所以存在以下情况:
 * 	1) 叶子结点被清空，释放叶子结点，同时删除其在父结点中的引用，并引出以下两个问题
 * 	    1))父结点的子树数不满足B树的要求，需要进行合并操作
 *	    2))父结点的子树数满足B树的要求 
 * 	2) 叶子结点未被清空，不作任何处理
 * 返回值:
 * 	非NULL: 该子结点不满足B树结点要求，需要进行合并操作
 * 	NULL: 子结点満足B树结点要求
 */
TreeNode* InternalTreeNode::del(int key)
{
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
	if(keys[i] >= key)
	    break;
    }
    
    TreeNode* p = child[i]->del(key);
    if(!p && p->isLeaf())
    {
	delete p;
	return NULL;
    }
    else
	return NULL;
    
    int half = (order >> 1);
    if(order % 2)
	half = half + 1;
    int minChildCount = half;
    
    //试图从兄弟结点中获取一个
    InternalTreeNode *q = NULL;
    int j = 0;
    for(j = 0; j < childCount; j++)
    {
	q = (InternalTreeNode *)child[j];
	if(q->childCount > minChildCount)
	    break;
    }
    
    if(j < childCount)
    {
	//找到有效的兄弟结点
	int tempKey = q->keys[q->keyCount - 1];
	TreeNode *s = q->child[q->childCount - 1];
	int k = 0;
	for(k = 0; k < keyCount; k++)
	{
	    if(tempKey <= q->keys[k])
		break;
	}
	p->addChild(k,s);
	//调整兄弟结点
	q->delChild(q->childCount -1);
	return NULL;
    }
    
    //未找到有效的兄弟结点，进行结点合并
    
    
    return this;
}
/**
 * 返回值: 返回合并后的结点
 */
TreeNode *InternalTreeNode::merge(int p)
{
    
}

/**
 * 删除子结点
 */
void InternalTreeNode::delChild(int p)
{
    for(int i = p; i < childCount - 1; i++)
	child[i] = child[i + 1];
    --childCount;
    child[childCount] == NULL;
    for(int i = p - 1; i < keyCount - 1; i++)
	keys[i] = keys[i + 1];
    --keyCount;
    keys[keyCount] = -1;
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
TreeNode* LeafTreeNode::del(int key)
{
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
	if(key == keys[i])
	    break;
    }
    for(int j = i; j < keyCount - 1; j++)
	keys[j] = keys[j + 1];
    keyCount--;
    
    if(keyCount == 0)
	return this;
    return NULL;
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
TreeNode* BTree::del(int key)
{
    return false;
}
void BTree::visit()
{
    
}
