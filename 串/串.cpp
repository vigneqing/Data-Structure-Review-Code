/* ═══════════════════════════════════════════════════════════════════
 * 串 (String) — 存储结构与基本操作
 * ═══════════════════════════════════════════════════════════════════ */

/* ─────────────────────────────────────────
 * 一、串的存储方式
 * ───────────────────────────────────────── */

//串的定长顺序存储
#define MAXLEN 255
typedef struct {
    char ch[MAXLEN];
    int length;
} SString;

/* ─── 1.1 堆分配存储 ─── */
//堆分配存储
typedef struct {
    char *ch;
    int length;
} HString;

HString S;
S.ch = (char *)malloc(MAXLEN * sizeof(char));
S.length = 0;

/* ─── 1.2 链式存储（低效，存储密度低） ─── */
//链式存储
typedef struct StringNode {
    char ch;//只有一个字节
    struct StringNode *next;//4B
}StringNode, *String;

//改进：每个结点存多个字符，提高存储密度
typedef struct StringNode {
    char ch[4];
    StringNode *next;
}StringNode, *String;


/* ─────────────────────────────────────────
 * 二、基本操作
 * ───────────────────────────────────────── */

//赋值
void StrAssign(SString &S, char *ch) {
    int i = 0;
    while (ch[i] != '\0') {
        S.ch[i] = ch[i];
        i++;
    }
    S.length = i;
}

//复制
void StrCopy(SString &Sub, SString S) {
    for (int i = 0; i < S.length; i++)
        Sub.ch[i] = S.ch[i];
    Sub.length = S.length;
}

//连接
void StrConcat(SString &S1, SString S2) {
    for (int i = 0; i < S2.length; i++)
        S1.ch[S1.length + i] = S2.ch[i];
    S1.length += S2.length;
}

//判空
bool StrEmpty(SString S) {
    return S.length == 0;
}

//求串长
int StrLength(SString S) {
    return S.length;
}

//清空
void ClearString(SString &S) {
    S.length = 0;
}

//销毁
void DestroyString(SString &S) {
    free(S.ch);
}


/* ─── 2.1 求子串 ─── */
//求字串 返回串S的第pos个字符起长度为len的子串
bool SubString(SString &Sub, SString S, int pos, int len) {
    if (pos + len - 1 > S.length)
        return false;
    for (int i = pos; i <pos + len; i++)
        Sub.ch[i-pos+1] = S.ch[i];
    Sub.length = len;
    return true;
}

/* ─── 2.2 比较与定位 ─── */
//比较
int StrCompare(SString S1, SString S2) {
    for (int i = 0; i < S1.length && i < S2.length; i++) {
        if (S1.ch[i] != S2.ch[i])
            return S1.ch[i] - S2.ch[i];
    }
    return S1.length - S2.length;
}

//串的定位
int Index(SString S, SString T) {
    int i = 1, n=StrLength(S), m=StrLength(T);
    SString Sub;
    while (i <= n - m + 1) {
        SubString(Sub, S, i, m);
        if (StrCompare(Sub, T) != 0) ++i;
        else return i;
    }
    return 0;
}



