//数位dp（数位统计）模板

//pos = 当前处理的位置（一般从高位到低位）
//pre = 上一个位的数字（更高的那一位）
//s = 要达到的状态，如果为1则可以认为找到了答案，到时候用来返回,给计数器+1。
//lim = 是否受限，也即当前处理这位能否随便取值。
//例如567：当前处理6这位。如果前面取的是4，则当前这位可以取0-9；
//                        如果前面取的5,那么当前这位就不能随便取，不然会超出这个数的范围。
//                        所以如果前面取5的话此时的lim=1,也就是说当前只可以取0-6。
//用dp数组保存这三个状态是因为往后转移的时候会遇到很多重复的情况。

//a[i]是记录数位的数组

//dp[i][0/1]表示当前第i位，前一位是否是某个数X的状态。是的话值为1，否则为0

typedef int Type;

Type dfs(int pos, int s, bool lim)
{
    if(pos == -1)
        return 1;
    if(!lim && ~dp[pos][s])
        return dp[pos][s];
    Type ret = 0;
    int u = lim ? a[pos] : 9;
    for(int i = first ? 1 : 0; i <= u; i++) //first是否是最高位。有的题目条件不允许前导零，所以如果前面位已经有1可以任意放，没有1则不能。
        ret += dfs(pos-1, i==6, lim&&i==u);
    return lim ? ret : dp[pos][s] = ret;
}


Type dfs(int pos,int pre,int s,bool lim)
{
    //已经搜到尽头,返回“是否找到了答案”这个状态
    if(pos == -1)
        return 1;

    //dp里保存的是完整的，即不受限的答案。所以如果满足的话，可以直接返回。
    if(!lim && ~dp[pos][pre][s])  //即dp[pos][pre][s] != -1
        return dp[pos][pre][s];

    int u = lim ? a[pos] : 9;   //是否受上一位（高位）数字的限制，u为本位数字的上限
    Type ret = 0;

    //往下搜的状态表示的很巧妙，s用||是因为如果前面找到了答案那么后面还有没有答案都无所谓了。而lim用&&是因为只有前面受限、当前受限才能推出下一步也受限。
    //比如567：如果是46X的情况，虽然6已经到尽头，但是后面的个位仍然可以随便取，因为百位没受限。所以如果个位要受限，那么前面必须是56。

    //这里用"不要49"一题来做例子。
    for(int i = first ? 1 : 0; i <= u; i++) //first是否是最高位。有的题目条件不允许前导零，所以如果前面位已经有1可以任意放，没有1则不能。
        ret += dfs(pos-1, i, s||(pre==4&&i==9), lim&&(i==u));

    //dp里保存完整的、取到尽头的数据
    return lim ? ret : dp[pos][pre][s] = ret;
}


//PS: __builtin_popcount()是一个GCC的内建函数，能精确计算二进制数中1的个数... 慎用，毕竟不确定比赛的时候编译器是否支持...
