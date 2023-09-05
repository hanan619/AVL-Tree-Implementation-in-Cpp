#ifndef AVL_Tree
#define AVL_Tree

class AVL;

class node
{
	friend class AVL;
private:
	int data;
	node* left;
	node* right;
public:
	node()
	{
		left = nullptr;
		right = nullptr;
	}
	node(int& x, node* l, node* r)
	{
		data = x;
		left = l;
		right = r;
	}
	bool isLeaf()
	{
		if (left == nullptr && right == nullptr)
			return true;

		return false;
	}

};

class AVL
{
public:
	AVL();
	AVL(node* r);
	AVL(AVL& A);
	bool isEmpty()
	{
		return root==nullptr;
	}
	int finMin()
	{
		return findMin(root)->data;
	}
	int findMax()
	{
		return findMax(root)->data;
	}
	bool add(int & x);
	bool remove(int x);
	int getRoot()
	{
		return root->data;
	}
	~AVL();

private:
	node* root;
	int item;
	node* copytree(node* & ptr);
	void destroytree(node* & ptr);
	void add(int & x, node* & ptr);
	bool remove(int x, node* & ptr);
	node* findMin(node* ptr);
	node* findMax(node* ptr);
	int height(node* ptr);
	void rotateR(node* & ptr);
	void rotateL(node* & ptr);
	int max(int x, int y)
	{
		return (x > y) ? x : y;
	}
};


#endif // !AVL
