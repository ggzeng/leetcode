
// 剑指 Offer 04. 二维数组中的查找
// https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/
#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1;
#define false 0;

bool find(int *array, int size, int target, int *idx);
bool findNumberIn2DArray(int **matrix, int matrixSize, int *matrixColSize, int target);

int main(void)
{
	bool found;
	int aa[][7] = {
		{1, 4, 7, 11, 15},
		{2, 5, 8, 12, 13, 19},
		{3, 6, 9, 16, 22},
		{10, 13, 14, 17, 18, 24, 25},
		{18, 21, 23, 26, 30}};
	int *matrix[] = {aa[0], aa[1], aa[2], aa[3], aa[4]};
	int matrixColSize[] = {5, 6, 5, 7, 5};

	if (findNumberIn2DArray(matrix, 5, matrixColSize, 5))
	{
		printf("found");
		return 0;
	}
	printf("not found");
	return 0;
}

/*
 * 输入 **matrix 是长度为 matrixSize 的数组指针的数组，其中每个元素（也是一个数组）
 * 的长度组成 *matrixColSize 数组作为另一输入，*matrixColSize 数组的长度也为 matrixSize
 */
bool findNumberIn2DArray(int **matrix, int matrixSize, int *matrixColSize, int target)
{
	bool ret;
	int *(*cc)[] = (int *(*)[])(matrix);
	int *colArray = malloc(sizeof(int) * matrixSize);
	for (int i = 0; i < matrixSize; i++)
	{
		colArray[i] = (*cc)[i][matrixColSize[i] - 1];
	}

	// get low row index
	int lowRow;
	if (find(colArray, matrixSize, target, &lowRow))
	{
		ret = true;
		goto END;
	}
	if (lowRow < 0)
	{
		ret = false;
		goto END;
	}

	// get low col index
	int lowCol;
	if (find((*cc)[matrixSize - 1], matrixColSize[matrixSize - 1], target, &lowCol))
	{
		ret = true;
		goto END;
	}

	if (lowCol < 0)
	{
		ret = false;
		goto END;
	}

	// find in small matrix
	for (int i = lowRow; i < matrixSize; i++)
	{
		for (int j = lowCol; j < matrixColSize[i]; j++)
		{
			if ((*cc)[i][j] == target)
			{
				ret = true;
				goto END;
			}
		}
	}
END:
	free(colArray);
	return ret;
}

// 在一个排序数组中通过二分发查找target所在的索引
// 1. 如果找到则返回true和对应的idx
// 2. 如果没找到则返回false和对应的可能包含此target的最小idx
// 2.1如果不存储在可能包含此target的idx则idx返回-1
bool find(int array[], int size, int target, int *idx)
{
	int pos = size / 2;
	int se_idx = -1;
	if (target == array[pos])
	{
		*idx = pos;
		return true;
	}
	if (target > array[pos])
	{
		if (size == 1)
		{
			*idx = -1;
			return false;
		}
		if (find(array + pos + 1, size - pos - 1, target, &se_idx))
		{
			*idx = pos + se_idx + 1;
			return true;
		}
		if (se_idx < 0)
		{
			*idx = -1;
			return false;
		}
		*idx += pos + se_idx + 1;
		return false;
	}

	// target < array[pos]
	if (size == 1)
	{
		*idx = 0;
		return false;
	}
	if (find(array, pos, target, &se_idx))
	{
		*idx = se_idx;
		return true;
	}
	if (se_idx < 0)
	{
		*idx = pos;
		return false;
	}
	*idx = se_idx;
	return false;
}