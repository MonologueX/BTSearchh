#pragma once
#include "Heap.h"
///////////////////////////////////
//头文件
#include <string.h>
#include <stdio.h>
#include <malloc.h>

typedef int BSTDataType;
typedef struct BSTNode
{
	struct BSTNode* _left;
	struct BSTNode* _right;
	//struct BSTNode* _parent;
	BSTDataType _data;
}BSTNode;

///////////////////////////////////
//函数代码

BSTNode* BuyBSTNode(BSTDataType x)
{
	BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
	node->_left = NULL;
	node->_right = NULL;
	node->_data = x;
	return node;
}

int BSTInsert(BSTNode** ppTree, BSTDataType x)
{
	if (*ppTree == NULL)
	{
		*ppTree = BuyBSTNode(x);
		return 0;
	}
	BSTNode* parent = NULL;
	BSTNode* cur = *ppTree;
	while (cur != NULL)
	{
		if (cur->_data > x)
		{
			parent = cur;
			cur = cur->_left;
		}
		else if (cur->_data < x)
		{
			parent = cur;
			cur = cur->_right;
		}
		else
		{
			return -1;
		}
	}
	cur = BuyBSTNode(x);
	if (parent->_data < x)
	{
		parent->_right = cur;
		//cur->_parent = parent;
	}
	else
	{
		parent->_left = cur;
		//cur->_parent = parent;
	}
	return 0;
}

int BSTRemoveAd(BSTNode** ppTree, BSTDataType x)
{
	BSTNode* parent = NULL;
	BSTNode* cur = *ppTree;
	while (cur)
	{
		if (cur->_data > x)
		{
			parent = cur;
			cur = cur->_left;
		}
		else if (cur->_data < x)
		{
			parent = cur;
			cur = cur->_right;
		}
		else
		{
			if (cur->_left != NULL && cur->_right != NULL)
			{
				BSTNode* left_child = cur->_left;
				parent = cur;
				while (left_child->_right != NULL)
				{
					parent = left_child;
					left_child = left_child->_right;
				}

				Swap(&left_child->_data, &cur->_data);
				cur = left_child;
			}

			if (cur->_left == NULL)
			{
				if (parent == NULL)
				{
					*ppTree = cur->_right;
				}
				else if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_right;
				}
			}
			else if (cur->_right == NULL)
			{
				if (parent == NULL)
				{
					*ppTree = cur->_left;
				}
				else if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
			}
			free(cur);
			return 0;
		}
	}
	return -1;
}

int BSTRemove(BSTNode** ppTree, BSTDataType x)
{
	BSTNode* del = NULL;
	BSTNode* cur = *ppTree;
	BSTNode* parent = *ppTree;
	while (cur)
	{
		if (cur->_data > x)
		{
			parent = cur;
			cur = cur->_left;
		}
		else if (cur->_data < x)
		{
			parent = cur;
			cur = cur->_right;
		}
		else
		{
			if (cur->_left != NULL && cur->_right != NULL)
			{
				BSTNode* left_child = cur->_left;
				parent = cur;
				while (left_child->_right != NULL)
				{
					parent = left_child;
					left_child = left_child->_right;
				}

				Swap(&left_child->_data, &cur->_data);
				cur = left_child;
			}
			del = cur;
			if (cur->_left == NULL)
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else if (parent->_right == cur)
				{
					parent->_right = cur->_right;
				}
				else if (parent == cur)
				{
					*ppTree = parent->_right;
				}
			}
			else if (cur->_right == NULL)
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else if (parent->_right == cur)
				{
					parent->_right = cur->_left;
				}
				else if (parent == cur)
				{
					*ppTree = parent->_left;
				}
			}
			else
			{
				BSTNode* subLeft = cur->_right;
				while (subLeft->_left)
				{
					parent = subLeft;
					subLeft = subLeft->_left;
				}

				del = subLeft;
				cur->_data = subLeft->_data;

				if (parent->_left == subLeft)
				{
					parent->_left = subLeft->_right;
				}
				else
				{
					parent->_right = subLeft->_right;
				}
			}
			free(del);
			del = NULL;
			return 0;
		}
	}
	return -1;
}

int BSTFind(BSTNode* pTree, BSTDataType x)
{
	BSTNode* cur = pTree;
	while (cur != NULL)
	{
		if (cur->_data > x)
		{
			cur = cur->_left;
		}
		else if (cur->_data < x)
		{
			cur = cur->_right;
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

void BSTDestory(BSTNode** ppTree)
{
	BSTNode* node = *ppTree;
	if (node == NULL)
	{
		return;
	}
	BSTDestory(&(node->_left));
	BSTDestory(&(node->_right));
	free(node);
	*ppTree = NULL;
}

void BSTInOrder(BSTNode* pTree)
{
	if (pTree == NULL)
	{
		return;
	}
	BSTInOrder(pTree->_left);
	printf("%d ", pTree->_data);
	BSTInOrder(pTree->_right);
}


int BSTFindR(BSTNode* pTree, BSTDataType x)
{
	if (pTree == NULL)
	{
		return -1;
	}
	if (pTree->_data == x)
	{
		return 0;
	}
	if (pTree->_data > x)
	{
		return BSTFindR(pTree->_left, x);
	}
	else
	{
		return BSTFindR(pTree->_right, x);
	}
}

int BSTInsertR(BSTNode** ppTree, BSTDataType x)
{
	if (*ppTree == NULL)
	{
		*ppTree = BuyBSTNode(x);
		return 0;
	}
	if ((*ppTree)->_data == x)
	{
		return -1;
	}
	else if ((*ppTree)->_data > x)
	{
		return BSTInsert(&((*ppTree)->_left), x);
	}
	else
	{
		return BSTInsert(&((*ppTree)->_right), x);
	}
}

int BSTRemoveR(BSTNode** ppTree, BSTDataType x)
{
	if ((*ppTree) == NULL)
	{
		return -1;
	}
	if ((*ppTree)->_data > x)
	{
		return BSTRemoveR(&(*ppTree)->_left, x);
	}
	else if ((*ppTree)->_data < x)
	{
		return BSTRemoveR(&(*ppTree)->_right, x);
	}
	else
	{
		BSTNode* del = *ppTree;
		if ((*ppTree)->_left == NULL)
		{
			*ppTree = (*ppTree)->_right;
			free(del);
		}
		else if ((*ppTree)->_right == NULL)
		{
			*ppTree = (*ppTree)->_left;
			free(del);
		}
		else
		{
			BSTNode* subLeft = (*ppTree)->_right;
			while (subLeft->_left)
			{
				subLeft = subLeft->_left;
			}
			(*ppTree)->_data = subLeft->_data;
			return BSTRemoveR(&(*ppTree)->_right, subLeft->_data);
		}
		return 0;
	}
	return -1;
}


///////////////////////////////////
//测试代码

void TestBSTInOrde()
{
	BSTNode* tree = NULL;
	BSTInsert(&tree, 5);
	BSTInsert(&tree, 2);
	BSTInsert(&tree, 6);
	BSTInsert(&tree, 7);
	BSTInsert(&tree, 9);
	BSTInsert(&tree, 7);
	BSTInsert(&tree, -1);
	BSTInOrder(tree);
	printf("\n");
}

void TestBSTRemove()
{
	BSTNode* tree = NULL;
	BSTInsert(&tree, 5);
	BSTInsert(&tree, 3);
	BSTInsert(&tree, 4);
	BSTInsert(&tree, 1);
	BSTInsert(&tree, 7);
	BSTInsert(&tree, 8);
	BSTInsert(&tree, 2);
	BSTInsert(&tree, 6);
	BSTInsert(&tree, 0);
	BSTInsert(&tree, 9);
	BSTInOrder(tree);
	printf("\n");

	BSTRemoveAd(&tree, 8);	
	BSTRemoveAd(&tree, 2);
	BSTRemoveAd(&tree, 1);
	BSTRemoveAd(&tree, 5);	
	BSTRemoveAd(&tree, 7);

	BSTInOrder(tree);
	printf("\n");
}

void TestBSTInsertR()
{
	BSTNode* tree = NULL;
	BSTInsertR(&tree, 5);
	BSTInsertR(&tree, 3);
	BSTInsertR(&tree, 4);
	BSTInsertR(&tree, 1);
	BSTInsertR(&tree, 7);
	BSTInsertR(&tree, 8);
	BSTInsertR(&tree, 2);
	BSTInsertR(&tree, 6);
	BSTInsertR(&tree, 0);
	BSTInsertR(&tree, 9);
	BSTInOrder(tree);
	printf("\n");

	BSTRemoveR(&tree, 8);
	BSTRemoveR(&tree, 2);
	BSTRemoveR(&tree, 1);
	BSTRemoveR(&tree, 5);
	BSTRemoveR(&tree, 7);

	BSTInOrder(tree);
	printf("\n");
}
