
// 剑指 Offer 04. 二维数组中的查找
// https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/
// 思路：第一层循环，第二次二分查找

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

	if (findNumberIn2DArray(matrix, 5, matrixColSize, 20))
	{
		printf("found");
		return 0;
	}
	printf("not found");
	return 0;
}

// 方法1：两层循环暴力查找法，简单也还算高效

int bin_search(int array[], int size, int target);

/*
 * 输入 **matrix 是长度为 matrixSize 的数组指针的数组，其中每个元素（也是一个数组）
 * 的长度组成 *matrixColSize 数组作为另一输入，*matrixColSize 数组的长度也为 matrixSize
 */
bool findNumberIn2DArray(int **matrix, int matrixSize, int *matrixColSize, int target)
{
	int idx;
	// int *(*mm)[] = (int *(*)[])(matrix);
	for (int i = 0; i < matrixSize; i++)
	{
		idx = bin_search(matrix[i], matrixColSize[i], target);
		if (idx >= 0)
		{
			return true;
		}
	}
	return false;
}

int bin_search(int array[], int size, int target)
{
	int ret;
	int pos;
	if (size == 0) // fix: input "[[]]"
	{
		return -1;
	}
	if (size == 1)
	{
		if (array[0] == target)
		{
			return 0;
		}
		return -1;
	}
	pos = size / 2;
	if (array[pos] == target)
	{
		return pos;
	}

	if (target > array[pos] && size > (pos + 1))
	{
		ret = bin_search(array + pos + 1, size - (pos + 1), target);
		if (ret < 0)
		{
			return ret;
		}
		return pos + ret + 1;
	}

	// target < array[pos]
	return bin_search(array, pos, target);
}
