//朴素模式匹配算法 O(nm)
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str, pattern;
    cout << "请输入字符串：";
    cin >> str;
    cout << "请输入模式：";
    cin >> pattern;
    int n = str.size(), m = pattern.size();
    for (int i = 0; i <= n - m; i++)
    {
        int j;
        for (j = 0; j < m; j++)
        {
            if (str[i + j] != pattern[j])   // 如果字符不匹配，跳出循环
                break;
        }
        if (j == m)   // 如果模式完全匹配，输出位置
        {
            cout << "模式在字符串中找到，位置为：" << i << endl;
            break;
        }
    }
    if (i == n - m)   // 如果模式未完全匹配，输出未找到
    {
        cout << "模式在字符串中未找到" << endl;
    }
    return 0;
}

//书上就是INDEX算法
int Index(SString S, String T){
    int i=1,j=1;
    while (i<=S.length&&j<=T.length){
        if (S[i]==T[j]){
            ++i;++j;
        }
        else{
            i=i-j+2;
            j=1;
        }
    }
    if (j>T.length)
        return i-T.length;
    else
        return 0;
}