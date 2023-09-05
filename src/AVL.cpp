#include "AVL.h"
#include<iostream>
using namespace std;

//CONTRUCTOR & DESTRUCTOR
AVL::AVL()
{
	root = nullptr;
	item = 0;
}
AVL::AVL(node* r)
{
	root = r;
	item = 1;
}
AVL::AVL(AVL& A)
{
	root = copytree(A.root);
	item = A.item;
}

AVL::~AVL()
{
	destroytree(root);
	root = nullptr;
}

//PUBLIC FUNCTIONS
bool AVL::add(int& x)
{
	add(x, root);
	item++;
	return true;
}

bool AVL::remove(int x)
{
	return remove(x, root);
}

//PRIVATE FUNCTIONS

node* AVL::copytree(node* &ptr)
{
	node* newNode = nullptr;
	if (ptr != nullptr)
	{
		newNode = new node(ptr->data, nullptr, nullptr);
		newNode->left = copytree(ptr->left);
		newNode->right = copytree(ptr->right);
	}
	return newNode;
}

void AVL::destroytree(node* &ptr)
{
	if (ptr != nullptr)
	{
		destroytree(ptr->left);
		destroytree(ptr->right);
		delete ptr;
	}
}

void AVL::add(int& x, node* & ptr)
{
	if (ptr == nullptr)
		ptr = new node(x, nullptr, nullptr);
	else
	{
		if (x < ptr->data)
			add(x, ptr->left);
		else if (x>ptr->data)
			add(x, ptr->right);

		if (height(ptr->left) > height(ptr->right) + 1)
			rotateR(ptr);
		else if (height(ptr->left) + 1 < height(ptr->right))
			rotateL(ptr);
	}
}

bool AVL::remove(int x, node* & ptr)
{
	bool condition = false;
	if (ptr == NULL)
		return false;  // Item not found; do nothing
	if (x < ptr->data)
	{
		condition = remove(x, ptr->left);
		if (height(ptr->left) > height(ptr->right) + 1)
			rotateR(ptr);
		else if (height(ptr->left) + 1 < height(ptr->right))
			rotateL(ptr);
		
	}
	else if (ptr->data < x)
	{
		condition = remove(x, ptr->right);
		if (height(ptr->left) > height(ptr->right) + 1)
			rotateR(ptr);
		else if (height(ptr->left) + 1 < height(ptr->right))
			rotateL(ptr);
	}
	else if (ptr->left != NULL && ptr->right != NULL) // Two children
	{
		ptr->data = findMin(ptr->right)->data;
		remove(ptr->data, ptr->right);
		return true;
	}
	else
	{
		node *oldNode = ptr;
		ptr = (ptr->left != NULL) ? ptr->left : ptr->right;
		delete oldNode;
		return true;
	}
	return condition;
}

node* AVL::findMin(node* ptr)
{
	if (ptr != nullptr)
	while (ptr->left != nullptr)
	{
		ptr = ptr->left;
	}
	return ptr;
}

node* AVL::findMax(node* ptr)
{
	if (ptr != nullptr)
	while (ptr->right != nullptr)
	{
		ptr = ptr->right;
	}
	return ptr;
}

void AVL::rotateR(node* & ptr)
{
	node*temp = ptr;
	ptr = ptr->left;
	temp->left = ptr->right;
	ptr->right = temp;
}

void AVL::rotateL(node* & ptr)
{
	node*temp = ptr;
	ptr = ptr->right;
	temp->right = ptr->left;
	ptr->left = temp;
}

int AVL::height(node* ptr)
{
	if (ptr == nullptr)
		return 0;
	else
		return 1 + max(height(ptr->left), height(ptr->right));
}