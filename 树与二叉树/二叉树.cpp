/* ═══════════════════════════════════════════════════════════════════
 * 二叉树 (Binary Tree)
 * ═══════════════════════════════════════════════════════════════════ */

/* ─────────────────────────────────────────
 * 一、存储结构
 * ───────────────────────────────────────── */

//顺序存储（只适合完全二叉树）
#define MaxSize 100
struct TreeNode{
    ElemType value;
    bool isEmpty;
};

TreeNode tree[MaxSize];

for(int i=0;i<MaxSize;i++){
    tree[i].isEmpty=true;
}

//链式存储
typedef struct BiTNode{
    ElemType data;
    struct BiTNode   *lchild,*rchild;
    // struct BiTNode *parent;        // 可选：三叉链表（指向父结点）
}BiTNode,*BiTree;

/* ─────────────────────────────────────────
 * 二、构造二叉树
 * ───────────────────────────────────────── */

//初始化空树
BiTree root=NULL;
//插入根节点
root=(BiTree)malloc(sizeof(BiTNode));
root->data = {1};
root->lchild = NULL;
root->rchild = NULL;
//插入新结点
BiTnode * p = (BiTNode *)malloc(sizeof(BiTNode));
p->data = {2};
p->lchild = NULL;
p->rchild = NULL;
root->lchild = p;
//插入新结点
BiTnode * q = (BiTNode *)malloc(sizeof(BiTNode));
q->data = {3};
q->lchild = NULL;
q->rchild = NULL;
root->rchild = q;


/* ═══════════════════════════════════════════════════════════════════
 * 三、遍历
 * ─────────────────────────────────────────
 *  方式        顺序           首/末特征
 *  先序     根 → 左 → 右    首个必是根
 *  中序     左 → 根 → 右    区分左右子树
 *  后序     左 → 右 → 根    末个必是根
 *  层次     逐层从左到右    用队列辅助
 * ═══════════════════════════════════════════════════════════════════ */

/* ─── 3.1 先序遍历 根左右 ─── */
void PreOrder(BiTree T){
    if(T!=NULL){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    // 中序: visit(T) 放中间; 后序: visit(T) 放最后
    }
}

/* ─── 3.2 求树的深度 ─── */
int treeDepth(BiTree T){
    if(T == NULL) {
        return 0;
    }
    else {
        int leftDepth = treeDepth(T->lchild);
        int rightDepth = treeDepth(T->rchild);
        return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
    }
}

/* ─── 3.3 层次遍历（广度优先，用队列） ─── */
//二叉树的结点
typedef struct BiTNode{
    char data;
    struct BiTNode   *lchild,*rchild;
}BiTNode,*BiTree;

//链式队列结点
typedef struct LinkNode{
    BiTNode *data;
    struct LinkNode *next;
}LinkNode;

typedef struct {
    LinkNode *front,*rear;
}LinkQueue;

void LevelOrder(BiTree T){
    LinkQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T);
    while(!QueueEmpty(Q)){
        DeQueue(Q, p);
        visit(p);
        if(p->lchild != NULL) {
            EnQueue(Q, p->lchild);
        }
        if(p->rchild != NULL) {
            EnQueue(Q, p->rchild);
        }
    }
}