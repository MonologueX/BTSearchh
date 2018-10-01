#pragma once
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#define TEST_HEADER printf("\n============%s============\n",__FUNCTION__)

typedef int HeapDataType;

typedef struct Heap
{
	HeapDataType* _a;
	size_t _size;
	size_t _capacity;
}Heap;

void HeapPrint(Heap* hp)
{
	assert(hp);
	for (size_t i = 0; i < hp->_size; ++i)
	{
		printf("%d ", hp->_a[i]);
	}
	printf("\n");
}

void Swap(HeapDataType* x1, HeapDataType* x2)
{
	HeapDataType x = *x1;
	*x1 = *x2;
	*x2 = x;
}

void HeapInit(Heap* hp, HeapDataType* a, size_t n)
{
	assert(hp);
	hp->_a = (HeapDataType*)malloc(sizeof(HeapDataType)* n);
	assert(hp->_a);
	hp->_size = n;
	hp->_capacity = n;
	for (size_t i = 0; i < n; ++i)
	{
		hp->_a[i] = a[i];
	}
}

void HeapAdjustDown(Heap *hp, int root)
{
	//assert(hp);
	int parent = root;
	size_t child = parent * 2 + 1;
	while (child < hp->_size)
	{
		if (child + 1<hp->_size && hp->_a[child + 1]<hp->_a[child])
		{
			child++;
		}
		if (hp->_a[child]<hp->_a[parent])
		{
			Swap(&(hp->_a[child]), &(hp->_a[parent]));
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapAdjustUp(Heap *hp, int child)
{
	assert(hp);
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (hp->_a[child] < hp->_a[parent])
		{
			Swap(&(hp->_a[child]), &(hp->_a[parent]));

			child = parent;
			parent = (child - 1) / 2;
			/*parent = (child - 1) >> 1;*/
		}
		else
		{
			break;
		}
	}
}

void CheckCapacity(Heap *hp)
{
	assert(hp);
	if (hp->_size == hp->_capacity)
	{
		hp->_capacity *= 2;
		hp->_a = (HeapDataType*)realloc(hp->_a, sizeof(HeapDataType)* hp->_capacity);
		assert(hp->_a);
	}
}

void HeapMark(Heap *hp)
{
	assert(hp);
	for (int i = (hp->_size - 2) / 2; i >= 0; --i)
	{
		HeapAdjustDown(hp, i);
	}
}

///////////////////////////////////////
//


void HeapkPush(Heap *hp, HeapDataType x)
{
	assert(hp);
	CheckCapacity(hp);

	hp->_a[hp->_size++] = x;
	HeapAdjustUp(hp, hp->_size - 1);
}

void HeapPop(Heap *hp)
{
	if (hp->_size > 0)
	{
		Swap(&(hp->_a[0]), &(hp->_a[hp->_size - 1]));
		hp->_size--;
		HeapAdjustDown(hp, 0);
	}
}

size_t MyHeapSize(Heap *hp)
{
	assert(hp);
	return hp->_size;
}

size_t HeapEmpty(Heap *hp)
{
	assert(hp);
	return hp->_size;
}

HeapDataType HeapTop(Heap *hp)
{
	assert(hp && hp->_size > 0);
	return hp->_a[0];
}

//////////////////////////////////////////////////////
//大堆 -- 升序
void AdjustDown(int* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && a[child + 1] > a[child])
		{
			++child;
		}
		if (a[child] > a[parent])
		{
			Swap(&(a[child]), &(a[parent]));
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int* a, const int n)
{
	assert(a);
	for (int i = (n - 2) / 2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}
	int end = n - 1;
	while (end > 1)
	{
		Swap(&(a[0]), &(a[end]));
		AdjustDown(a, end, 0);
		--end;
	}
}

//最小的前K个
void HeapTopK(int* a, const int n, int k)
{
	int* heap = (int*)malloc(sizeof(int)*k);
	for (int i = 0; i < k; ++i)
	{
		heap[i] = a[i];
	}
	for (int i = (k - 2) / 2; i >= 0; --i)
	{
		AdjustDown(heap, k, i);
	}
	for (int j = k; j < n; ++j)
	{
		if (a[j] < heap[0])
		{
			heap[0] = a[j];
		}
		AdjustDown(heap, k, 0);
	}
	for (int i = 0; i < k; ++i)
	{
		printf("%d ", heap[i]);
	}
	printf("\n");
	free(heap);
}
