/**
 * 备注
 *  来自网上速度最快的代码
 * 点评
 *  性能其实和我的差不多。相比原来的代码我这里做些优化，那就是
 *  strlen()函数只使用了一次，原代码在最外层循环的条件判断处都有使用。
 * 结果
 *  118 / 118 个通过测试用例
 *  状态：通过
 *  执行用时：0 ms
 *  内存消耗：5.7 MB
 */
char * longestCommonPrefix(char ** strs, int strsSize){
    if(strsSize==0)
    {
        return "";
    }
    int max_len = strlen(strs[0]);
    for(int i=0;i<max_len;i++)
    {
        for(int j=1;j<strsSize;j++)
        {
            if(strs[0][i]!=strs[j][i])
            {
                strs[0][i]='\0';
                max_len = i;
                break;
            }
        }
    }
    return strs[0];
}
