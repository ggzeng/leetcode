
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rearrangeBarcodes(int* barcodes, int barcodesSize, int* returnSize){
    int temp;
    for (int i = 0; i < barcodesSize; i++) {
        for (int j = i+1; j < barcodesSize; j++) {
            if (barcodes[i] == barcodes[j]) {
                continue;
            }
            temp =  barcodes[i+1];
            barcodes[i+1] = barcodes[j];
            barcodes[j] = temp;
        }
    }
    *returnSize=barcodesSize;
    return barcodes;
}
/*
 * 上面这种方式无法解决下面这种情况，并且也不符合题目的内存释放要求
输入
[1,1,1,1,2,2,3,3]
输出
[1,3,2,3,1,2,1,1]
预期结果
[1,3,1,3,1,2,1,2]
*/

