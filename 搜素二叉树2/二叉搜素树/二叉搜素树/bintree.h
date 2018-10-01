#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<string.h>
#include <windows.h>
#define TEST_HEADER printf("\n============%s============\n",__FUNCTION__)
typedef char BTDataType;

typedef struct Node
{
	BTDataType _data;
	struct BTNode* pLeft;
	struct BTNode* pRight;
}Node, *BTNode;

#include "queue.h"

/////////////////////////////////////
//函数代码
/////////////////////////////////////

BTNode BuyBTNode(BTDataType data)
{
	BTNode pNewNode = (BTNode)malloc(sizeof(Node));
	assert(pNewNode);
	pNewNode->_data = data;
	pNewNode->pLeft = NULL;
	pNewNode->pRight = NULL;
	return pNewNode;
}

void _CreateBinaryTree(BTNode* pRoot, BTDataType* array, int size, int *index, BTDataType invalid)
{
	assert(index);
	if ((*index) < size && invalid != array[*index])
	{
		*pRoot = BuyBTNode(array[*index]);
		//
		++(*index);
		_CreateBinaryTree(&(*pRoot)->pLeft, array, size, index, invalid);
		//
		++(*index);
		_CreateBinaryTree(&(*pRoot)->pRight, array, size, index, invalid);
	}
}

void CreateBinaryTree(BTNode* pRoot, BTDataType* array, int size, BTDataType invalid)
{
	int index = 0;
	_CreateBinaryTree(pRoot, array, size, &index, invalid);
}

BTNode CopyBinTree(BTNode pRoot)
{
	BTNode pNewRoot = NULL;
	if (pRoot)
	{
		pNewRoot = BuyBTNode(pRoot->_data);
		pNewRoot->pLeft = CopyBinTree(pRoot->pLeft);
		pNewRoot->pRight = CopyBinTree(pRoot->pRight);
	}
	return pNewRoot;
}

//前序
void PreOrder(BTNode pRoot)
{
	if (pRoot)
	{
		printf("%c ", pRoot->_data);
		PreOrder(pRoot->pLeft);
		PreOrder(pRoot->pRight);
	}
}

//中序
void InOrder(BTNode pRoot)
{
	if (pRoot)
	{
		InOrder(pRoot->pLeft);
		printf("%c ", pRoot->_data);
		InOrder(pRoot->pRight);
	}
}

//后序
void PostOrder(BTNode pRoot)
{
	if (pRoot)
	{
		PostOrder(pRoot->pLeft);
		PostOrder(pRoot->pRight);
		printf("%c ", pRoot->_data);
	}
}

void LevelOrder(BTNode pRoot)
{
	if (pRoot == NULL)
	{
		return;
	}

	Queue q;
	QueueInit(&q);
	QueuePush(&q, pRoot);
	while (QueueSize(&q))
	{
		BTNode front = QueueFront(&q);
		printf("%c ", front->_data);
		QueuePop(&q);
		if (front->pLeft)
		{
			QueuePush(&q, front->pLeft);
		}
		if (front->pRight)
		{
			QueuePush(&q, front->pRight);
		}
	}
	printf("\n");
}

//void DestoryBinTree(BTNode* pRoot)
//{
//	assert(pRoot);
//	if (*pRoot)
//	{
//		DestoryBinTree((*pRoot)->pLeft);
//		DestoryBinTree((*pRoot)->pRight);
//		free(*pRoot);
//		*pRoot = NULL;
//	}
//}

int BTreeIsComplete2(BTNode pRoot)
{
	if (pRoot == NULL)
	{
		printf("是完全二叉树！\n");
		return 1;
	}
	Queue q;
	QueueInit(&q);
	QueuePush(&q, pRoot);
	int flag = 0;
	while (QueueSize(&q))
	{
		BTNode front = QueueFront(&q);
		if (front->pLeft != NULL)
		{
			if (1 == flag)
			{
				printf("不是完全二叉树！\n");
				return 0;
			}
			else
			{
				QueuePush(&q, front->pLeft);
			}
		}
		else
		{
			flag = 1;
		}
		if (front->pRight != NULL)
		{
			if (1 == flag)
			{
				printf("不是完全二叉树！\n");
				return 0;
			}
			else
			{
				QueuePush(&q, front->pRight);
			}
		}
		else
		{
			flag = 1;
		}
		QueuePop(&q);
	}
	printf("是完全二叉树\n");
	return 1;
}

void BTreeIsComplete(BTNode pRoot)
{
	if (pRoot == NULL)
	{
		printf("是完全二叉树！\n");
		return;
	}
	Queue q;
	QueueInit(&q);
	QueuePush(&q, pRoot);
	while (QueueSize(&q))
	{
		BTNode front = QueueFront(&q);
		if (front == NULL)
		{
			break;
		}
		QueuePop(&q);
		QueuePush(&q, front->pLeft);
		QueuePush(&q, front->pRight);
	}
	while (QueueSize(&q))
	{
		BTNode front = QueueFront(&q);
		if (QueueFront(&q) == NULL)
		{
			QueuePop(&q);
		}
		else
		{
			printf("不是完全二叉树！\n");
			return;
		}
	}
	printf("是完全二叉树\n");
	return;
}

//二叉树中节点个数
int Size(BTNode pRoot)
{
	int LeftSize = 0;
	int RightSize = 0;
	if (NULL == pRoot)
	{
		return 0;
	}
	LeftSize = Size(pRoot->pLeft);
	RightSize = Size(pRoot->pRight);

	return LeftSize + RightSize + 1;
}

//二叉树中叶子节点个数
int GetLeafCount(BTNode pRoot)
{
	if (NULL == pRoot)
	{
		return 0;
	}
	if (NULL == pRoot->pLeft && NULL == pRoot->pRight)
	{
		return 1;
	}
	return GetLeafCount(pRoot->pLeft) + GetLeafCount(pRoot->pRight);
}

//第k层节点个数
int GetKLevalCount(BTNode pRoot, int k)
{
	assert(k > 0);
	if (NULL == pRoot)
	{
		return 0;
	}
	if (1 == k)
	{
		return 1;
	}
	return GetKLevalCount(pRoot->pLeft, k - 1)
		+ GetKLevalCount(pRoot->pRight, k - 1);
}

int BTDepth(BTNode pRoot)
{
	if (NULL == pRoot)
	{
		return 0;
	}
	int leftDepth = BTDepth(pRoot->pLeft);
	int rightDepth = BTDepth(pRoot->pRight);
	return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}

BTNode BTFind(BTNode pRoot, BTDataType x)
{
	if (NULL == pRoot)
	{
		return NULL;
	}
	if (pRoot->_data == x)
	{
		return pRoot;
	}
	BTNode ret = BTFind(pRoot->pLeft, x);
	if (ret)
	{
		return ret;
	}
	/*BTNode ret = BTFind(pRoot->pRight, x);
	if (ret)
	{
	return ret;
	}*/
	return BTFind(pRoot->pRight, x);
	return NULL;
}

//////////////////////////////////////
//笔记
//////////////////////////////////////
//递归改成非递归
//1. 循环
//2. 栈模拟

#include "Stack.h"
//////////////////////////////////////
//笔记
//////////////////////////////////////
//左路节点
//左路节点右数  --- 子问题

//前序
void PreOrderNor(BTNode pRoot)
{
	Stack s;
	StackInit(&s);
	BTNode cur = pRoot;
	while (cur || StackSize(&s) != 0)
	{
		// 访问以一颗的开始
		// 左路节点
		while (cur)
		{
			printf("%c ", cur->_data);
			StackPush(&s, cur);
			cur = cur->pLeft;
		}

		BTNode top = StackTop(&s);
		StackPop(&s);

		//子问题
		cur = top->pRight;
	}
	printf("\n");
}

//中序
void InOrderNor(BTNode pRoot)
{
	Stack s;
	StackInit(&s);
	BTNode cur = pRoot;
	while (cur || StackSize(&s) != 0)
	{
		// 访问以一颗的开始
		// 左路节点
		while (cur)
		{
			StackPush(&s, cur);
			cur = cur->pLeft;
		}

		BTNode top = StackTop(&s);
		printf("%c ", top->_data);
		StackPop(&s);

		//子问题
		cur = top->pRight;
	}
	printf("\n");
}

//后序
void PostOrderNor(BTNode pRoot)
{
	Stack s;
	StackInit(&s);
	BTNode last = NULL;
	BTNode cur = pRoot;
	while (cur || StackSize(&s) != 0)
	{
		// 访问以一颗的开始
		// 左路节点
		while (cur)
		{
			StackPush(&s, cur);
			cur = cur->pLeft;
		}
		BTNode top = StackTop(&s);
		//右为空 或者右树根节点为 data 表示已经访问过了
		if (top->pRight == NULL || top->pRight == last)
		{
			printf("%c ", top->_data);
			last = top;
			StackPop(&s);
		}
		else
		{
			cur = top->pRight;
		}
	}
	printf("\n");
}
