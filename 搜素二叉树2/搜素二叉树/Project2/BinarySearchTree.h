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
//int BSTDestory(BSTNode** ppTree)
//{
//
//}

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
