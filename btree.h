/**
 *An implementation of B-Tree, considration of design pattern
 *For now, the invalid keys or values are integer and not less than zero.
 **/
#include <stddef.h> //包含NULL的定义
class BTree;
class TreeNode
{
public:
    TreeNode(){};
    virtual ~TreeNode(){};
    //whether the node is full or not
    virtual bool isFull() = 0;
    //从树中搜索指定的关键字，并返回其值，若不存在则返回-1
    virtual int search(int key) = 0;
    //在树中添加一个新的键值对，若已存在，则返回NULL
    virtual TreeNode* insert(int key,int value) = 0;
    //指树中删除指定的键
    virtual TreeNode* del(int key) = 0;
    //遍历B树
    virtual void visit() = 0;
    //当前结点是否是叶结点
    virtual bool isLeaf() = 0;
    //返回树的最大键
    virtual int getMaxKey() = 0;
    //返回树的最小键
    virtual int getMinKey() = 0;
    //在当前结点的指定位置添加新的子结点
    virtual void addChild(int p,TreeNode *t) = 0;
    virtual void addChild(TreeNode *t) = 0;
    //删除当前结点指定位置处的子结点 
    virtual void delChild(int p) = 0;
    virtual void delChild(TreeNode *p) = 0;
protected:
    //在位置p处分割结点
    virtual TreeNode* split(int p) = 0;
    //在位置p处结点
    virtual TreeNode* merge(int p,int q) = 0;
};
class InternalTreeNode : public TreeNode
{
public:
    InternalTreeNode(int order);
    virtual ~InternalTreeNode();
    int search(int key);
    TreeNode* insert(int key,int value);
    TreeNode* del(int key);
    void visit();
    bool isLeaf()
    {
        return false;
    }
    bool isFull()
    {
	return childCount == order;
    }
    int getMaxKey();
    int getMinKey();
    
    void addChild(int p,TreeNode* t);
    void addChild(TreeNode *p);
    void delChild(int p);
    void delChild(TreeNode *p);
    TreeNode** getChild(){return child;};
    int getChildCount(){return childCount;};
protected:
    TreeNode* split(int p);
    TreeNode* merge(int p,int q);
private:
    int keyCount;
    int childCount;
    int *keys;
    TreeNode** child;
    int order;
};
class LeafTreeNode: public TreeNode
{
public:
    LeafTreeNode(int order);
    virtual ~LeafTreeNode();
    int search(int key);
    TreeNode* insert(int key,int value);
    TreeNode* del(int key);
    void visit();
    bool isLeaf()
    {
        return true;
    }
    bool isFull()
    {
	return (keyCount + 1) == order;
    }
    int getMaxKey();
    int getMinKey();
    
    void addChild(int p,TreeNode* t){};
    void addChild(TreeNode *t){};
    void delChild(int p){};
    void delChild(TreeNode *p){};
protected:
    TreeNode* split(int p){return NULL;};
    TreeNode* merge(int p,int q){return NULL;};
private:
    int keyCount;
    int *keys;
    int *values;
    int order;
};
class BTree
{
public:
    BTree(int order);
    ~BTree();
    int search(int key);
    bool insert(int key,int value);
    bool del( int key );
    void visit();
private:
    int order;
    TreeNode *root;
};