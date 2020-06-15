/*
 * 备注
 *   来自网上速度最快的代码。
 * 点评
 *   相对自己的代码，巧妙的地方是用一个数组就表示了所有等式的情况。
 *   另外通过不断查找父节点来判断是否是一个链。所以等式链的顺序是没关系的,
 *   无论等式的连接顺序为何终点都相同，并且都是一个等于自己的节点(x=x)。
 *   如果是链上新增的等式，那么把这个点挂到终点之上即可(x=y)。
 */

#define MAXCHAR 26
int father[MAXCHAR] = {0};


int find(int x) {
   if (father[x] == x) {
       return x;
   }
   return find(father[x]);
}

void union_find(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy){
        father[fx] = fy;
    }
    return ;
}

bool equationsPossible(char ** equations, int equationsSize){
    if (equationsSize == 0) {
        return false;
    }

    for (int i = 0; i < MAXCHAR; i++) {
        father[i] = i;
    }

    for (int j = 0; j < equationsSize; j++) {
        if (equations[j][1] == '=') {
            union_find(equations[j][0]-'a', equations[j][3]-'a');
        }
    }

    int flag = true;
    for(int k = 0; k < equationsSize; k++) {
        if (equations[k][1] == '!') {
            int x = find(equations[k][0] - 'a');
            int y = find(equations[k][3] - 'a');
            if (x == y) {
                flag = false;
            }
        }
    } 

    // 全局变量恢复初始值
    for (int i = 0; i < MAXCHAR; i++) {
        father[i] = 0;
    }
    return flag;
}

