/* ═══════════════════════════════════════════════════════════════════
 * 队列 (Queue) — FIFO 先进先出
 * ═══════════════════════════════════════════════════════════════════ */

/* ─────────────────────────────────────────
 * 一、顺序队列（循环队列）
 * ───────────────────────────────────────── */

//队列FIFO
#define MaxSize 10
typedef struct {
    ElemType data[MaxSize];
    int front,rear;  //队头和队尾指针
}SqQueue;

/* ─── 1.1 初始化与判空 ─── */
//初始化队列
void InitQueue(SqQueue &Q){
    //初始时，队头尾都指向0
    Q.rear = Q.front = 0;
}

void testQueue(){
    //
    SqQueue Q;
    InitQueue(Q);
}

//判断队列是否为空
bool QueueEmpty(SqQueue Q){
    return Q.rear == Q.front;
}

/* ─── 1.2 入队（循环） ─── */
//入队操作
bool EnQueue(SqQueue &Q,ElemType x){
    if((Q.rear+1)%MaxSize==Q.front)//队列已满
        return false;
    Q.data[Q.rear]=x;
    Q.rear=(Q.rear + 1)%MaxSize; //将队列变成循环的
    return true;
}

/* ─── 1.3 出队（循环） ─── */
//出队
bool DeQueue(SqQueue &Q,ElemType &x){
    if(Q.rear==Q.front)//队列已空
        return false;
    x=Q.data[Q.front];
    Q.front=(Q.front+1)%MaxSize;//队头指针后移
    return true;
}

/* ─── 1.4 取队头 ─── */
//查找
bool GetHead(SqQueue Q,ElemType &x){
    if(Q.rear==Q.front)
        return false;
    x=Q.data[Q.front];
    return true;
}

/* ─── 1.5 判满/判空的三种方案 ─── */
//元素个数 (rear+MaxSize-front)%MaxSize

//方案一：牺牲一个存储单元  (rear+1)%MaxSize==front
//方案二：增加 size 变量记录长度
//方案三：增加 tag 标记最后一次操作是插入还是删除
/*
判断队列已满/已空
方案一：头尾位置
方案二：加个size
方案三：头=尾加上一个判断最后是插入还是删除的tag
大部分队尾指针指向的是队尾元素的后一个位置
*/


/* ─────────────────────────────────────────
 * 二、链式队列
 * ───────────────────────────────────────── */

//链式队列结点
typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;

typedef struct {
    LinkNode *front,*rear;
}LinkQueue;

/* ─── 2.1 初始化（带头结点） ─── */
void InitQueue(LinkQueue &Q){
    //初始时 front和rear都指向头结点
    Q.front=Q.rear=(LinkNode*)malloc(sizeof(LinkNode));
    Q.front->next=NULL;
}

void testLinkQueue(){
    LinkQueue Q;
    InitQueue(Q);
}

/* ─── 2.2 入队（带头结点） ─── */
void EnQueue(LinkQueue &Q,ElemType x){
    LinkNode *s=(LinkNode *)malloc(sizeof(LinkNode));
    s->data=x;
    s->next=NULL;
    Q.rear->next=s;
    Q.rear=s;
}

/* ─── 2.3 入队（不带头结点，需特殊处理） ─── */
void EnQueue(LinkQueue &Q,ElemType x){
    LinkNode *s=(LinkNode *)malloc(sizeof(LinkNode));
    s->data=x;
    s->next=NULL;
    if(Q.front == NULL) {//特殊处理
        Q.front = s;
        Q.rear = s;
    }else {
        Q.rear->next=s;
        Q.rear=s;
    }
}

/* ─── 2.3 出队（不带头结点） ─── */
//队头元素出队(不带头结点)
bool DeQueue(LinkQueue &Q,ElemType &x){
    if(Q.front==Q.rear)
        return false;
    LinkNode *p=Q.front->next;
    x=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)//最后一个结点
        Q.rear=Q.front;
    free(p);
    return true;
}

