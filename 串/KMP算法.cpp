//KMP算法 O(m+n)
#include <iostream>
#include <string>
using namespace std;

void KMP(string str, string pattern) {
    int n = str.size();
    int m = pattern.size();
    int next[m];
    getNext(pattern, next);

    int i = 0, j = 0;
    while (i < n && j < m) {
        if (j == -1 || str[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j == m) {
        cout << "模式串在主串中出现的位置是：" << i - m << endl;
    } else {
        cout << "模式串在主串中未出现" << endl;
    }
}

void getNext(string pattern, int next[]) {
    int m = pattern.size();
    next[0] = -1;
    int j = -1;
    for (int i = 1; i < m; i++) {
        while (j != -1 && pattern[i] != pattern[j + 1]) {
            j = next[j];
        }
        if (pattern[i] == pattern[j + 1]) {
            j++;
        }
        next[i] = j;
    }
    cout << "next数组为：" << endl;
    for (int i = 0; i < m; i++) {
        cout << next[i] << " ";
    }
    cout << endl;
}

int main() {
    string str = "ababababab";
    string pattern = "abab";
    KMP(str, pattern);
    return 0;
}

//书上的
int Index_KMP(SString S, SString T,int next[]){
    int i=1,j=1;
    while(i<=S.length&&j<=T.length){
        if(j==0||S.ch[i]==T.ch[j]){
            ++i;
            ++j;
        }
        else
            j=next[j];
    }
    if(j>T.length)
        return i-T.length;
    else
        return 0;
}

//求next数组（只要求手算就行）
//eg不是书上的
void GetNext(SString T,int next[]){
    int i=1,j=-1;
    next[0]=-1;
    while(i<T.length){
        if(j==-1||T.ch[i]==T.ch[j+1]){
            ++i;
            ++j;
            next[i]=j;
        }
        else
            j=next[j];
    }
}

//next数组的优化

