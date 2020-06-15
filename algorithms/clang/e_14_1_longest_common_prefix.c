/**
 * 思路
 *   比较字符串数组中的两个字符串，以最短的公共字符串为基准继续比较。
 * 过程
 *   刚开始开始想用字符树之类的操作，后来想想没必要。
 *   当输入的数组为空时，刚开始返回了一个空字符'\0'导致错误，应该返回空字符串""。
 *   因为前者返回是字符，后者是指针。
 * 要点
 */
int compare2str(char *a, char *b) {
    int max_len = 0;
    for (; a[max_len]!='\0'&&b[max_len]!='\0'; max_len++) {
        if (a[max_len] == b[max_len]) continue;
        break;
    }
    return max_len;
}

char * longestCommonPrefix(char ** strs, int strsSize){
    if (strsSize <= 0) {
        return "";
    }
    int max_len;
    int len = 0;
    char *max_prefix=strs[0];
    max_len = strlen(max_prefix);
    for(int i=1; i<strsSize; i++) {
        len = compare2str(max_prefix, strs[i]);
        if (len < max_len) {
            max_len = len;
        }
        max_prefix[max_len] = '\0';
    }
    return max_prefix;
}

