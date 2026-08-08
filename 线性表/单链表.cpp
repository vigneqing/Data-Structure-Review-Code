//单链表
struct LNode {
    ElemType data;
    struct LNode *next;
};

struct LNode *p = (struct LNode *)malloc(sizeof(struct LNode));//动态申请一个结点

//更简单
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

//要声明一个指向单链表第一个结点的指针
//LNode *L;或者LinkList L; 前者强调是一个结点，后者强调是一个链表

//初始化不带头结点的单链表
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

bool InitList(LinkList &L) {
    L = NULL; //将指针置为空
    return true;
}

void test() {
    LinkList L;//声明一个指向单链表第一个结点的指针
    //初始化一个空表
    InitList(L);
    //.........
}

//判断单链表是否为空
bool ListEmpty(LinkList L) {
    return (L == NULL);
}

//初始化带头节点的单链表
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

bool InitList(LinkList &L) {
    L = (LNode *)malloc(sizeof(LNode)); //创建头结点
    if(!L) return false; //内存分配失败
    //或者 if(L == NULL) return false;
    L->next = NULL; //将头结点的指针域置为空
    return true;
}

void test() {
    LinkList L;//声明一个指向单链表第一个结点的指针
    //初始化一个空表
    InitList(L);
    //.........
}

//判断单链表是否为空
bool ListEmpty(LinkList L) {
    return (L->next == NULL);
}

//单链表的基本操作--插入
//按位序插入（带头节点）O(n)
bool ListInsert(LinkList &L, int i, ElemType e) {
    if(i<1) return false; //插入位置不合法
    /*
    LNode *p = L; //指向头结点
    int j = 0; //指示当前p指向的是第几个结点
    while(p!=NULL && j<i-1) { //寻找第i-1个结点
        p = p->next;
        j++;
    }
    */
   //使用GetElem函数代替上面的while循环
   LNode *p = GetElem(L, i-1); //寻找第i-1个结点
    /*
    if(!p) return false; //插入位置不合法
    LNode *s = (LNode *)malloc(sizeof(LNode)); //创建新结点
    s->data = e; //将数据元素赋值给新结点
    s->next = p->next; //将新结点的指针域指向第i个结点
    p->next = s; //将第i-1个结点的指针域指向新结点
    return true;
    */
   //这一段代码可以改成后面的后插函数
   return ListInsertNext(p, e);
}

//不带头结点的单链表插入操作（就是对i=1的时候特殊处理） O(n)
bool ListInsert(LinkList &L, int i, ElemType e) {
    if(i<1) return false; //插入位置不合法
    if(i==1) { //在表头插入
        LNode *s = (LNode *)malloc(sizeof(LNode)); //创建新结点
        s->data = e; //将数据元素赋值给新结点
        s->next = L; //将新结点的指针域指向原来的第一个结点
        L = s; //头指针指向新结点
        return true;
    }
    LNode *p = L; //指向第一个结点
    int j = 1; //指示当前p指向的是第几个结点
    while(p!=NULL && j<i-1) { //寻找第i-1个结点
        p = p->next;
        j++;
    }
    /*
    if(!p) return false; //插入位置不合法
    LNode *s = (LNode *)malloc(sizeof(LNode)); //创建新结点
    s->data = e; //将数据元素赋值给新结点
    s->next = p->next; //将新结点的指针域指向第i个结点
    p->next = s; //将第i-1个结点的指针域指向新结点
    return true;
    */
    //这一段代码可以改成后面的后插函数
   return ListInsertNext(p, e);
}

//指定结点的后插操作 O(1)
bool ListInsertNext(LNode *p, ElemType e) {
    if(p==NULL) return false; //插入位置不合法
    LNode *s = (LNode *)malloc(sizeof(LNode)); //创建新结点
    if(s == NULL) return false; //内存分配失败
    s->data = e; //将数据元素赋值给新结点
    s->next = p->next; //将新结点的指针域指向第i个结点
    p->next = s; //将第i-1个结点的指针域指向新结点
    return true;
}

//前插操作 O(1)
bool ListInsertPrior(LNode *p, ElemType e) {
    if(p==NULL) return false; //插入位置不合法
    LNode *s = (LNode *)malloc(sizeof(LNode)); //创建新结点
    if(s == NULL) return false; //内存分配失败
    s->data = p->data; //将p结点的数据元素赋值给新结点
    s->next = p->next; //将新结点的指针域指向p结点的后继结点
    p->next = s; //将p结点的指针域指向新结点
    p->data = e; //将e赋值给p结点的数据域
    return true;
}

//书上：
bool InsertPriorNode(LNode *p, ElemType e) {
    if(p == NULL || s == NULL) return false; //插入位置不合法
    s->next = p->next; //将新结点的指针域指向p结点的后继结点
    p->next = s; //将p结点的指针域指向新结点
    ElemType temp = p->data; //将p结点的数据元素赋值给临时变量
    p->data = s->data; //将新结点的数据元素赋值给p结点
    s->data = temp; //将临时变量的值赋值给新结点的数据域
    return true;
}

//按位序删除（带头结点）O(n)
bool ListDelete(LinkList &L, int i, ElemType &e) {
    if(i<1) return false; //删除位置不合法
    /*
    LNode *p = L; //指向头结点
    int j = 0; //指示当前p指向的是第几个结点
    while(p!=NULL && j<i-1) { //寻找第i-1个结点
        p = p->next;
        j++;
    }
    */
    //使用GetElem函数代替上面的while循环
    LNode *p = GetElem(L, i-1); //寻找第i-1个结点
    if(p==NULL || p->next==NULL) return false; //删除位置不合法
    LNode *q = p->next; //指向第i个结点
    e = q->data; //将第i个结点的数据元素赋值给e
    p->next = q->next; //将第i-1个结点的指针域指向第i+1个结点
    free(q); //释放第i个结点的内存空间
    return true;
}

//指定结点的删除 O(1)
bool DeleteNode(LNode *p) {
    if(p==NULL || p->next==NULL) return false; //删除位置不合法
    LNode *q = p->next; //指向第i+1个结点
    p->data = q->data; //将第i+1个结点的数据元素赋值给第i个结点
    p->next = q->next; //将第i个结点的指针域指向第i+2个结点
    free(q); //释放第i+1个结点的内存空间
    return true;
}

//单链表按位查找O(n)
LNode *GetElem(LinkList &L, int i) {
    if(i<0) return NULL; //查找位置不合法
    LNode *p = L; //指向头结点
    int j = 0; //指示当前p指向的是第几个结点
    while(p!=NULL && j<i) { //寻找第i个结点
        p = p->next;
        j++;
    }
    return p; //返回第i个结点的指针
}

//按值查找O(n)
LNode *LocateElem(LinkList &L, ElemType e) {
    LNode *p = L; //指向头结点
    while(p!=NULL && p->data!=e) { //寻找值为e的结点
        p = p->next;
    }
    return p; //返回值为e的结点的指针
}

//求表的长度O(n)
int ListLength(LinkList L) {
    int length = 0; //初始化长度为0
    LNode *p = L; //指向头结点
    while(p!=NULL) { //遍历链表
        length++; //长度加1
        p = p->next; //指向下一个结点
    }
    return length; //返回长度
}

//尾插法建立单链表O(n)
LinkList List_TailInsert(LinkList &L) {
    LNode *newnode, *tail; //newnode为新结点，tail为尾指针
    int x;
    L = (LNode *)malloc(sizeof(LNode)); //创建头结点
    tail = L; //tail指向头结点
    scanf("%d", &x); //输入第一个数据元素
    while(x != 9999) { //输入结束标志为9999
        newnode = (LNode *)malloc(sizeof(LNode)); //创建新结点
        newnode->data = x; //将数据元素赋值给新结点
        tail->next = newnode; //将新结点插入到链表尾部
        tail = newnode; //tail指向新的尾结点
        scanf("%d", &x); //输入下一个数据元素
    }
    tail->next = NULL; //尾结点的指针域置为空
    return L; //返回链表头指针
}

//头插法建立单链表O(n)
LinkList List_HeadInsert(LinkList &L) {
    LNode *newnode; //newnode为新结点
    int x;
    L = (LNode *)malloc(sizeof(LNode)); //创建头结点
    L->next = NULL; //头结点的指针域置为空
    scanf("%d", &x); //输入第一个数据元素
    while(x != 9999) { //输入结束标志为9999
        newnode = (LNode *)malloc(sizeof(LNode)); //创建新结点
        newnode->data = x; //将数据元素赋值给新结点
        newnode->next = L->next; //将新结点插入到链表头部
        L->next = newnode; //将头结点的指针域指向新结点
        scanf("%d", &x); //输入下一个数据元素
    }
    return L; //返回链表头指针
}