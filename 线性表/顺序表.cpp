/* ═══════════════════════════════════════════════════════════════════
 * 顺序表 (Sequential List)
 * 用连续存储空间存放线性表，随机存取 O(1)，插入删除 O(n)
 * ═══════════════════════════════════════════════════════════════════ */

/* ─────────────────────────────────────────
 * 一、静态分配
 * ───────────────────────────────────────── */

//静态分配
#define MaxSize 10
typedef struct {
    ElemType data[MaxSize];
    int length;
} SqList;

// 示例：顺序表的初始化
#include <stdlib.h>
#define MaxSize 10
typedef struct {
    int data[MaxSize];//分配了MaxSize*sizeof(int)的连续空间
    int length;
} SqList;

//初始化顺序表
void InitList(SqList &L) {
    for(int i=0; i<MaxSize; i++) {
        L.data[i] = 0; //初始化数据为0
    }
    L.length = 0; //初始化长度为0
}

int main() {
    SqList L;
    InitList(L);
    //后续操作......
    //此时如果没有给每个数据初始化，直接对数据进行操作的话
    //应该用for(int i=0; i<L.length; i++)来遍历数据
    return 0;
}

/* ─────────────────────────────────────────
 * 二、动态分配
 * ───────────────────────────────────────── */

//动态分配
#define InitSize 10
typedef struct {
    ElemType *data; //指示动态分配数组的指针
    int MaxSize;
    int length;
} SqList;

/* ─── 2.1 内存申请与释放 ─── */
//C语言：malloc / free
L.data = (ElemType *)malloc(InitSize * sizeof(ElemType)); 
free(L.data); 
//C++：new / delete
L.data = new ElemType[InitSize]; 
delete[] L.data; 

/* ─── 2.2 动态分配示例 ─── */
//示例：动态分配
#include <stdlib.h>
#define InitSize 10
typedef struct {
    int *data; //指示动态分配数组的指针
    int MaxSize;
    int length;
} SeqList;

void InitList(SeqList &L) {
    L.data = (int *)malloc(InitSize * sizeof(int));
    L.MaxSize = InitSize;
    L.length = 0;
}
//增加动态数组的长度
void IncreaseSize(SeqList &L, int len) {
    int *p = L.data;
    L.data=(int *)malloc((L.MaxSize + len) * sizeof(int));
    for(int i=0; i<L.length; i++) {
        L.data[i] = p[i];
    }
    L.MaxSize += len;
    free(p);
}
//realloc 重新分配（注意：可能失败返回NULL导致原指针丢失）
void ReallocSize(SeqList &L, int newMaxSize) {
    int *p = (int *)realloc(L.data, newMaxSize * sizeof(int));
    if(p) {
        L.data = p;
        L.MaxSize = newMaxSize;
    } else {
        //处理内存分配失败的情况
        free(L.data);
        L.data = NULL;
        L.MaxSize = 0;
        L.length = 0;
    }
}
//【注意】realloc 失败时可能返回NULL，导致原指针丢失（内存泄漏）

int main() {
    SeqList L;
    InitList(L);
    //后续操作......
    IncreaseSize(L, 5); //增加动态数组的长度
    ReallocSize(L, 15); //重新分配内存空间
    return 0;
}




/* ═══════════════════════════════════════════════════════════════════
 * 三、基本操作
 * ═══════════════════════════════════════════════════════════════════ */

/* ─── 3.1 插入 O(n) ─── */
//顺序表的基本操作--插入 O(n)
#define MaxSize 10
typedef struct {
    int data[MaxSize];
    int length;
} SqList;
//在顺序表L的第i个位置插入元素e
void ListInsert(SqList &L, int i, int e) {
    for(int j=L.length;j>=i;j--)//将第i个位置及之后的元素后移
        L.data[j]=L.data[j-1];
    L.data[i-1]=e;
    L.length++;
}
//完善版（带合法性检查）
bool ListInsert(SqList &L, int i, int e) {
    if(i<1 || i>L.length+1) 
        return false; //插入位置不合法
    if(L.length>=MaxSize) 
        return false; //顺序表已满
    for(int j=L.length;j>=i;j--)//将第i个位置及之后的元素后移
        L.data[j]=L.data[j-1];
    L.data[i-1]=e;
    L.length++;
    return true;
}

int main() {
    SqList L;
    InitList(L);
    //......
    ListInsert(L, 3, 3);
    return 0;
}

/* ─── 3.2 删除 O(n) ─── */
//顺序表的基本操作--删除 O(n)
bool ListDelete(SqList &L, int i, int &e) {
    if(i<1 || i>L.length) 
        return false; //删除位置不合法
    e = L.data[i-1]; //将被删除的元素赋值给e
    for(int j=i;j<L.length;j++)//将第i个位置之后的元素前移
        L.data[j-1]=L.data[j];
    L.length--;
    return true;
}

int main() {
    SqList L;
    InitList(L);
    //......
    int e = -1;
    if (ListDelete(L, 3, e)) 
        std::cout << "Deleted element: " << e << std::endl;
    else 
        std::cout << "Deletion failed." << std::endl;
    return 0;
}

/* ─── 3.3 按位查找 O(1) ─── */
//顺序表的核心优势：随机存取
#define InitSize 10
typedef struct {
    ElemType *data;//指示动态分配数组的指针
    int MaxSize;
    int length;
} SeqList;

ElemType GetElem(SeqList L, int i){
    return L.data[i-1];
}

/* ─── 3.4 按值查找 O(n) ─── */
typedef struct {
    ElemType *data;//指示动态分配数组的指针
    int MaxSize;
    int length;
} SeqList;
int LocateElem(SeqList L, ElemType e){
    for(int i=0; i<L.length; i++){
        if(L.data[i] == e)
            return i+1; //返回元素e的位序
    }
    return 0; //未找到元素e
}