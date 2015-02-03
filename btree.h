/**
 *An implementation of B-Tree, considration of design pattern
 **/
#include <stddef.h> //包含NULL的定义
class TreeNode
{
public:
    virtual int getKeyCount() = 0;
    virtual int getChildCount() = 0;
    virtual bool search(int key) = 0;
    virtual TreeNode insert(int key) = 0;
    virtual bool del(int key) = 0;
    virtual void visit() = 0;
    virtual bool isLeaf() = 0;
    virtual int getMaxKey() = 0;
    virtual int getMinKey() = 0;
    virtual int* getKeys() = 0;
    virtual int getKeyCount() = 0;
    virtual int getChildCount() = 0;
    virtual TreeNode* getChildren() = 0;
    
    /**
     *添加删除子结点，只有内部结点有效
     */
    virtual void addChild(int p,TreeNode t) = 0;
    virtual void delChild(TreeNode t) = 0;
protected:
    virtual TreeNode split(int p) = 0;
};
class InternalTreeNode : public TreeNode
{
public:
    InternalTreeNode(int order);
    ~InternalTreeNode();
    int getKeyCount()
    {
	return keyCount;
    }
    int *getKeys()
    {
	return keys;
    }
    int getChildCount()
    {
	return childCount;
    }
    TreeNode *getChildren()
    {
	return child;
    }
    bool search(int key);
    TreeNode insert(int key);
    bool del(int key);
    void visit();
    bool isLeaf()
    {
	return false;
    }
    int getMaxKey();
    int getMinKey();
    
    void addChild(int p,TreeNode t);
    void delChild(TreeNode t);
protected:
    TreeNode split(int p);
private:
    int keyCount;
    int childCount;
    int *keys;
    TreeNode *child;
    int order;
};
class LeafTreeNode: public TreeNode
{
public:
    LeafTreeNode(int order);
    ~LeafTreeNode();
    int getKeyCount()
    {
	return keyCount;
    }
    int *getKeys()
    {
	return keys;
    }
    int getChildCount()
    {
	return 0;
    }
    TreeNode *getChildren()
    {
	return NULL;
    }
    bool search(int key);
    TreeNode insert(int key);
    bool del(int key);
    void visit();
    bool isLeaf()
    {
	return true;
    }
    int getMaxKey();
    int getMinKey();
    int *getKeys();
    TreeNode *getChildren();
    
    void addChild(int p,TreeNode t){};
    void delChild(TreeNode t){};
protected:
    TreeNode split(int p)
    {
	return NULL;
    }
private:
    int keyCount;
    int *keys;
    int order;
};
class BTree
{
public:
    Btree();
    ~Btree();
    void search(int key);
    bool insert(int key);
    bool del(int key);
    void visit();
private:
    int order;
    TreeNode *root;
};