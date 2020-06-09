/**
 * 解题思路：把每个等式链(a=b=c=...)存放到一个数组中，如果有多个
 * 不相关的等式链那么就有多个数组。然后在检查不等式，如果不等式
 * 两边的数在一个链表中那么就返回false。
 * 解题过程：虽然有“链”的关系，但是由于a~z范围较小，一开始想到的就是用
 * 数组保存和查找而非链表。但是刚开始题目理解有问题，把不等式也当做
 * 一个"链"来处理了。不等式是不能传递的，a!=b,b!=c，并不能说明a!=c。
 * 另外由于说到表达式的个数不会超过500个，所以一开始就申请了两个
 * (一个等式，一个不等式，其实不等式是不需要保存的) 500*26 的数组，运行
 * 过程中提示了内存问题。后来改成动态申请26个字符的内存。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    true=1,
    false=0
}bool;

int getListIdx(char ** ql, int rowNum, char c) {
    if (rowNum < 0) {
        return -1;
    }
    for (int i=0; i <= rowNum; i++) {
        if (ql[i][c-'a'] == c) {
            return i;
        }
    }
    return -1;
}

void mergeList(char ** ql, int row1, int row2, int *maxRow) {
    int temp;
    if (row1 == row2) {
        return;
    }
    if (row1 > row2 ) {
        temp = row1;
        row1 = row2;
        row2 = temp;
    }
    for (int i=0; i < 26; i++) {
        if (ql[row2][i] != 0) {
            ql[row1][i] = ql[row2][i];
            ql[row2][i] = 0;
        }
    }
    if (row2 == *maxRow) {
        free(ql[row2]);
        ql[row2] = NULL;
        (*maxRow)--;
        return;
    }
    mergeList(ql, row2, *maxRow, maxRow);
    return;
}

void freeList(char **ql, int rowNum) {
    for (int i=0; i<rowNum; i++) {
        if (ql[i] != NULL) {
            free(ql[i]);
        }
    }
}

void save2list(char *eq, char ** ql, int *maxRow) {
    int idx1;
    int idx2;
    idx1 = getListIdx(ql, *maxRow, eq[0]);
    if (idx1 < 0) {
        idx2 = getListIdx(ql, *maxRow, eq[3]);
        if (idx2 < 0) {
            (*maxRow)++;
            ql[*maxRow] = malloc(27);
            memset(ql[*maxRow], 0, 27);
            ql[*maxRow][eq[0] - 'a'] = eq[0];
            ql[*maxRow][eq[3] - 'a'] = eq[3];
        } else {
            ql[idx2][eq[0] - 'a'] = eq[0];
        }
    } else {
        idx2 = getListIdx(ql, *maxRow, eq[3]);
        if (idx2 < 0) {
            ql[idx1][eq[3] - 'a'] = eq[3];
        } else {
            mergeList(ql, idx1, idx2, maxRow);
        }
    }
    return;
}

bool equationsPossible(char ** equations, int equationsSize){
    int maxRow = equationsSize;
    char *eql[maxRow];
    int eqlRowNum = -1;

    memset(eql, 0, sizeof(eql));
    int idx1;
    int idx2;

    // save
    for (int i=0; i<equationsSize; i++) {
        if (equations[i][1] == '=') {
            save2list(equations[i], eql, &eqlRowNum);
        }
    }

    // check
    for (int i=0; i<equationsSize; i++) {
        if (equations[i][1] == '!') {
            if (equations[i][0] == equations[i][3]) {
                return false;
            }
            idx1 = getListIdx(eql, eqlRowNum, equations[i][0]);
            idx2 = getListIdx(eql, eqlRowNum, equations[i][3]);
            if (idx1 == idx2 && idx1 >= 0 && idx2 >= 0) {
                return false;
            }
        }
    }
    return true;
}

int main(void)
{
    bool res;
    char *equations[10] = {
        "a==b",
        "b!=a"
    };

    res = equationsPossible(equations, 2);
    printf("case1: res is %d, except is 0\n", res);

    equations[0] = "a==b";
    equations[1] = "b!=c";
    equations[2] = "c==a";
    res = equationsPossible(equations, 3);
    printf("case2: res is %d, except is 0\n", res);

    equations[0] = "a!=a";
    res = equationsPossible(equations, 1);
    printf("case3: res is %d, except is 0\n", res);

    equations[0] = "c==c";
    equations[1] = "b==d";
    equations[2] = "x!=z";
    res = equationsPossible(equations, 3);
    printf("case4: res is %d, except is 1\n", res);

    equations[0] = "a==b";
    equations[1] = "e==c";
    equations[2] = "b==c";
    equations[3] = "a!=e";
    res = equationsPossible(equations, 4);
    printf("case5: res is %d, except is 0\n", res);

    equations[0] = "e==e";
    equations[1] = "d!=e";
    equations[2] = "c==d";
    equations[3] = "d!=e";
    res = equationsPossible(equations, 4);
    printf("case6: res is %d, except is 1\n", res);

    equations[0] = "a!=i";
    equations[1] = "g==k";
    equations[2] = "k==j";
    equations[3] = "k!=i";
    equations[4] = "c!=e";
    equations[5] = "a!=e";
    equations[6] = "k!=a";
    equations[7] = "a!=g";
    equations[8] = "g!=c";
    res = equationsPossible(equations, 9);
    printf("case7: res is %d, except is 1\n", res);

    return 0;
}
