/* ═══════════════════════════════════════════════════════════════════
 * 栈 (Stack) — LIFO 后进先出
 * ═══════════════════════════════════════════════════════════════════ */

/* ─────────────────────────────────────────
 * 一、顺序栈
 * ───────────────────────────────────────── */

//顺序栈的定义LIFO
#define MaxSize 10
typedef struct {
    int data[MaxSize]; //存储栈元素的数组
    int top; //栈顶指针
} SqStack;

//初始化
void InitStack(SqStack &S){
    S.top = -1; //初始化栈顶指针
}

void testSqStack()
{
    SqStack S; //定义顺序栈
    InitStack(S);
}

//进栈操作
bool Push(SqStack &S,ElemType x){
    if(S.top == MaxSize-1) //栈满，报错
        return false;
    S.top = S.top + 1;
    S.data[S.top]= x ;
    //或者
    //S.data[++S.top] = x;
    return true;
}

//出栈操作
bool Pop(SqStack &S , ElemType &x){
    if(S.top == -1)
        return false;
    x=S.data[S.top];
    S.top = S.top -1;
    //或者
    //x = S.data[S.top--];
    return true;
}

//读取栈顶元素
bool GetTop(SqStack S,ElemType &x){
    if(S.top == -1)
        return false;
    x = S.data[S.top];
    return true;
}


/* ─────────────────────────────────────────
 * 二、共享栈（两个栈共享同一数组空间）
 * ───────────────────────────────────────── */

//共享栈
#define MaxSize 10
typedef struct {
    Elemtype data[MaxSize];
    int top0;
    int top1;
}ShStack;

//初始化共享栈
void InitStack(ShStack &S){
    S.top0 = -1;
    S.top1 = MaxSize;
}


/* ─────────────────────────────────────────
 * 三、链栈（链式存储的栈，头插法实现）
 * ───────────────────────────────────────── */

//栈链（链式栈）
typedef struct Linknode{
    ElemType data;
    struct Linknode *next;
}*LiStack;  //LiStack 是指向节点的指针类型

/* ─── 3.1 初始化与判空 ─── */
//初始化链栈
void InitStack(LiStack &S){
    S = NULL;  //栈为空时，栈顶指针指向NULL
}

//判断栈空
bool StackEmpty(LiStack S){
    return S == NULL;
}

/* ─── 3.2 进栈（头插法，新结点始终作为新栈顶） ─── */
//进栈操作（头插法，新节点始终作为新的栈顶）
bool Push(LiStack &S, ElemType x){
    Linknode *p = (Linknode*)malloc(sizeof(Linknode));
    if(p == NULL)  //内存分配失败
        return false;
    p->data = x;
    p->next = S;  //新节点指向原栈顶
    S = p;        //更新栈顶指针
    return true;
}

/* ─── 3.3 出栈 ─── */
bool Pop(LiStack &S, ElemType &x){
    if(S == NULL)  //栈空
        return false;
    Linknode *p = S;  //暂存栈顶节点
    x = p->data;       //取出数据
    S = p->next;       //栈顶指针后移
    free(p);           //释放原栈顶节点
    return true;
}

/* ─── 3.4 取栈顶与销毁 ─── */
//读取栈顶元素
bool GetTop(LiStack S, ElemType &x){
    if(S == NULL)
        return false;
    x = S->data;
    return true;
}

//销毁链栈
void DestroyStack(LiStack &S){
    Linknode *p;
    while(S != NULL){
        p = S;
        S = S->next;
        free(p);
    }
}
