#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i, j;
    int num1, num2;
    int *returnNums = (int *)malloc(sizeof(int)*2);
    if (!returnNums) {
        return NULL;
    }
    for (i = 0; i < numsSize; i++) {
        num1 = nums[i];
        for (j = i+1; j < numsSize; j++) {
            num2 = nums[j];
            if ((num1 + num2) == target) {
                returnNums[0] = i;
                returnNums[1] = j;
                *returnSize = 2;
                return returnNums;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}


int* twoSum(int* nums, int numsSize, int target, int* returnSize);

int main(void) {
    int rtnSize;
    int nums[] = {2, 7, 11, 15};
    int *rtnNums;
    rtnNums = twoSum((int *)nums, 4, 9, &rtnSize);
    if (rtnNums) {
        printf("[%d, %d]\n", rtnNums[0], rtnNums[1]);
        free(rtnNums);
    } else {
        printf("not found!\n");
    }
}
