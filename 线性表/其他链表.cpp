/* ═══════════════════════════════════════════════════════════════════
 * 其他链表类型：双链表 / 循环链表 / 静态链表
 * ═══════════════════════════════════════════════════════════════════ */

/* ─────────────────────────────────────────
 * 一、双链表 (Double Linked List)
 * ───────────────────────────────────────── */

//双链表的初始化（带头结点）
typedef struct DNode
{
    ElemType data; //数据域
    struct DNode *prior; //前驱指针
    struct DNode *next; //后继指针
} DNode, *DLinkList;

//初始化双链表
bool InitDLinkList(DLinkList &L)
{
    L = (DNode *)malloc(sizeof(DNode)); //创建头结点
    if (!L) //内存分配失败
        return false;
    L->prior = NULL; //头结点的前驱指针置空
    L->next = NULL; //头结点的后继指针置空
    return true;
}

void testDLinkList()
{
    DLinkList L;
    if (InitDLinkList(L))
        printf("双链表初始化成功！\n");
    else
        printf("双链表初始化失败！\n");
}

/* ─── 1.1 后插操作 ─── */
//双链表的插入（后插）
bool InsertNextDNode(DNode *p, DNode *s){
    if (p == NULL || s == NULL) //判断指针是否为空
        return false;
    s->next = p->next; //将s的后继指针指向p的后继结点
    if (p->next != NULL) //如果p的后继结点不为空
        p->next->prior = s; //将p的后继结点的前驱指针指向s
    s->prior = p; 
    p->next = s; 
    return true;
}

/* ─── 1.2 删除操作 ─── */
//双链表的删除
bool DeleteNextDNode(DNode *p){
    if(p == NULL ) return false; //判断指针是否为空
    DNode *q = p->next; 
    if(q == NULL) return false; //如果p的后继结点为空，返回false
    p->next = q->next; 
    if(q->next != NULL) 
        q->next->prior = p;  
        free(q); //释放q结点的内存空间
    return true; 
}

/* ─── 1.3 销毁与遍历 ─── */(DLinkList &L){
    while (L->next != NULL) //当链表不为空时
    {
        DeleteNextDNode(L); //删除头结点的后继结点
    }
    free(L); //释放头结点的内存空间
    L = NULL; //将链表指针置空
}

//双链表的遍历 
void TraverseDLinkList(DLinkList L){
    DNode *p = L->next; //从头结点的后继结点开始遍历
    while (p != NULL) //当p不为空时
    {
        //...
        p = p->next; //指针后移
    }
}



/* ─────────────────────────────────────────
 * 二、循环单链表 (Circular Singly Linked List)
 * ───────────────────────────────────────── */

//循环单链表
typedef struct CNode
{
    ElemType data; //数据域
    struct CNode *next; //后继指针
} CNode, *CLinkList;

//初始化循环单链表
bool InitCLinkList(CLinkList &L)
{
    L = (CNode *)malloc(sizeof(CNode)); //创建头结点
    if (!L) //内存分配失败
        return false;
    L->next = L; //头结点的后继指针指向自身，形成循环
    return true;
}

//判断循环单链表是否为空
bool IsEmpty(CLinkList L)
{
    return L->next == L; //如果头结点的后继指针指向自身，则链表为空
}

//判断结点p是否为循环单链表的最后一个结点
bool IsLast(CLinkList L, CNode *p)
{
    return p->next == L; //如果结点p的后继指针指向头结点，则p为最后一个结点
}

/* ─────────────────────────────────────────
 * 三、循环双链表 (Circular Doubly Linked List)
 * ───────────────────────────────────────── */
bool InitCDLinkList(CLinkList &L)
{
    L = (CNode *)malloc(sizeof(CNode)); //创建头结点
    if (!L) //内存分配失败
        return false;
    L->prior = L; 
    L->next = L; 
    return true;
}

void testCLinkList()
{
    CLinkList L;
    if (InitCLinkList(L))
        printf("循环单链表初始化成功！\n");
    else
        printf("循环单链表初始化失败！\n");
}

bool IsEmpty(CLinkList L)
{
    return L->next == L; //如果头结点的后继指针指向自身，则链表为空
}

bool isLast(CLinkList L, CNode *p)
{
    return p->next == L; //如果结点p的后继指针指向头结点，则p为最后一个结点
}

//循环双链表的插入（无需判断空，因为是循环的）
bool InsertNextDNode(DNode *p, DNode *s){
    s->next = p->next; //将s的后继指针指向p的后继结点
    p->next->prior = s; //将p的后继结点的前驱指针指向s
    s->prior = p; 
    p->next = s; 
    return true;
}//不用判断空



/* ─────────────────────────────────────────
 * 四、静态链表 (Static Linked List)
 * 用数组模拟链表，通过 next 下标串联，适合不支持指针的语言
 * ───────────────────────────────────────── */

//静态列表
#define MAXSIZE 10
struct Node
{
    ElemType data; 
    int next; 
};

void testSLinkList(){
    struct Node SList[MAXSIZE]; //静态链表
    //...........
}

// 课本版本：用 typedef 数组定义
#define MAXSIZE 10
typedef struct
{
    ElemType data; 
    int next; 
} SqList[MAXSIZE];

//静态链表的初始化
void InitSLinkList(SqList &L)
{
    for (int i = 0; i < MAXSIZE - 1; i++)
    {
        L[i].next = i + 1; //将每个结点的next指针指向下一个结点
    }
    L[MAXSIZE - 1].next = -1; //最后一个结点的next指针置为-1，表示链表结束
}

//静态链表的插入
bool InsertSLinkList(SqList &L, int i, ElemType e)
{
    if (i < 0 || i >= MAXSIZE) //判断插入位置是否合法
        return false;
    int j = L[MAXSIZE - 1].next; //获取空闲结点的下标
    if (j == -1) //如果没有空闲结点，返回false
        return false;
    L[MAXSIZE - 1].next = L[j].next; //将空闲结点的next指针指向下一个空闲结点
    L[j].data = e; //将数据域赋值为e
    L[j].next = L[i].next; //将新结点的next指针指向第i个结点的后继结点
    L[i].next = j; //将第i个结点的next指针指向新结点
    return true;
}