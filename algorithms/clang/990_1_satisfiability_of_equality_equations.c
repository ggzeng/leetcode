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
        ql[row2] = 0;
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
            ql[*maxRow] = malloc(26);
            memset(ql[*maxRow], 26, 0);
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
    char *nel[maxRow];
    int nelRowNum = -1;

    memset(eql, maxRow, 0);
    memset(eql, maxRow, 0);
    int idx1;
    int idx2;
    for (int i=0; i<equationsSize; i++) {
        if (equations[i][1] == '=') {
            idx1 = getListIdx(nel, nelRowNum, equations[i][0]);
            idx2 = getListIdx(nel, nelRowNum, equations[i][3]);
            if (idx1 >= 0 && idx2 >= 0) {
                return false;
            }
            save2list(equations[i], eql, &eqlRowNum);
        } else {
            idx1 = getListIdx(eql, eqlRowNum, equations[i][0]);
            idx2 = getListIdx(eql, eqlRowNum, equations[i][3]);
            if (idx1 >= 0 && idx2 >= 0) {
                return false;
            }
            save2list(equations[i], nel, &nelRowNum);
        }
    }
    return true;
}

void main(void)
{
    bool res;
    char *equations[] = {
        "a==b",
        "b!=a"
    };

    res = equationsPossible(equations, sizeof(equations)/8);
    printf("res is %d, except is 0\n", res);
        
    return;
}
