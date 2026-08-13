/* ═══════════════════════════════════════════════════════════════════
 * 树与森林 (Tree & Forest)
 * ─────────────────────────────────────────────────────────────────
 *  树的三种存储结构：双亲表示法 / 孩子表示法 / 孩子兄弟表示法
 *  树的遍历：先根、后根、层次（用队列）
 *  森林的遍历：先序（= 对应二叉树的先序）、中序（= 对应二叉树的中序）
 *  说明：孩子兄弟表示法可把树/森林直接转换成二叉树
 * ═══════════════════════════════════════════════════════════════════ */

/* ─────────────────────────────────────────
 * 一、双亲表示法（顺序存储）
 * 每个结点只存"双亲在数组中的下标"
 * 优点：找双亲 O(1)；缺点：找孩子要遍历整个数组 O(n)
 * ───────────────────────────────────────── */

#define MAX_TREE_SIZE 100
typedef struct{                     //树中结点类型
    ElemType data;                  //数据域
    int parent;                     //双亲在数组中的下标（根结点为 -1）
}PTNode;

typedef struct{                     //树的类型
    PTNode nodes[MAX_TREE_SIZE];    //结点数组
    int n;                          //结点总数
}PTree;

/* ─────────────────────────────────────────
 * 二、孩子表示法（顺序 + 链式）
 * 顺序存储各结点，每个结点的所有孩子串成一条链表
 * 优点：找孩子方便；缺点：找双亲要遍历所有链表
 * ───────────────────────────────────────── */

struct CTNode{                      //孩子链表中的结点
    int child;                      //孩子结点在数组中的下标
    struct CTNode *next;            //指向下一个孩子结点
};

typedef struct{                     //数组中的每个元素（每个结点）
    ElemType data;                  //数据域
    struct CTNode *firstchild;      //指向第一个孩子（孩子链表头指针）
}CTBox;

typedef struct{                     //树的类型
    CTBox nodes[MAX_TREE_SIZE];     //结点数组
    int n,r;                        //n：结点总数，r：根结点的下标
}CTree;

/* ─────────────────────────────────────────
 * 三、孩子兄弟表示法（链式存储，最常用）
 * 左指针 firstchild → 第一个孩子
 * 右指针 nextsibling → 右兄弟
 * 树/森林 → 二叉树 的转换正是基于这种表示法
 * ───────────────────────────────────────── */

typedef struct CSNode{
    ElemType data;                                  //数据域
    struct CSNode *firstchild,*nextsibling;         //第一个孩子和右兄弟指针
}CSNode,*CSTree;

/* ═══════════════════════════════════════════════════════════════════
 * 四、树的遍历（孩子兄弟表示法下）
 * ─────────────────────────────────────────
 *  遍历方式      访问顺序              对应二叉树
 *  先根遍历     根 → 各子树           先序遍历
 *  后根遍历     各子树 → 根           中序遍历
 *  层次遍历     逐层从左到右          用队列辅助
 * ═══════════════════════════════════════════════════════════════════ */

/* ─── 4.1 树的先根遍历（等效于二叉树的先序遍历） ─── */
//先访问根结点，再依次先根遍历根结点的每一棵子树
//孩子兄弟表示法：firstchild 是第一棵子树，nextsibling 是其余各棵子树
void PreOrder(CSTree T){
    if(T!=NULL){
        visit(T);                   //先访问根结点
        PreOrder(T->firstchild);    //先根遍历第一棵子树
        PreOrder(T->nextsibling);   //先根遍历其余各棵子树
    }
}

/* ─── 4.2 树的后根遍历（等效于二叉树的中序遍历） ─── */
//先依次后根遍历根结点的每一棵子树，最后访问根结点
void PostOrder(CSTree T){
    if(T!=NULL){
        PostOrder(T->firstchild);   //后根遍历第一棵子树
        visit(T);                   //访问根结点
        PostOrder(T->nextsibling);  //后根遍历其余各棵子树
    }
}

/* ─── 4.3 树的层次遍历（广度优先，用队列实现） ─── */
//链式队列结点（队列元素为树的结点指针 CSNode*）
typedef struct LinkNode{
    CSNode *data;
    struct LinkNode *next;
}LinkNode;

typedef struct{
    LinkNode *front,*rear;
}LinkQueue;

//根入队 → 出队访问 → 该结点的所有孩子入队 → 循环直到队空
void LevelOrder(CSTree T){
    LinkQueue Q;
    InitQueue(Q);
    if(T!=NULL)
        EnQueue(Q,T);               //根结点入队
    while(!QueueEmpty(Q)){
        CSNode *p;
        DeQueue(Q,p);               //队头结点出队
        visit(p);                   //访问出队结点
        //孩子兄弟表示法中，结点 p 的所有孩子连在
        //firstchild 开头的 nextsibling 链上，依次全部入队
        for(p=p->firstchild;p!=NULL;p=p->nextsibling)
            EnQueue(Q,p);
    }
}

/* ═══════════════════════════════════════════════════════════════════
 * 五、森林的遍历
 * 森林 = m(m≥0) 棵互不相交的树，各树根结点用 nextsibling 串起来
 * 因此森林遍历与"对应二叉树"的遍历完全等效
 * ═══════════════════════════════════════════════════════════════════ */

/* ─── 5.1 森林的先序遍历（等效于二叉树的先序遍历） ─── */
//即对每个树先根遍历：
//① 访问第一棵树的根 ② 先序遍历根结点的子树森林 ③ 先序遍历其余树构成的森林
void PreOrderForest(CSTree T){
    if(T!=NULL){
        visit(T);                       //① 访问第一棵树的根结点
        PreOrderForest(T->firstchild);  //② 先序遍历根结点的子树森林
        PreOrderForest(T->nextsibling); //③ 先序遍历其余树构成的森林
    }
}

/* ─── 5.2 森林的中序遍历（等效于二叉树的中序遍历） ─── */
//即对每个树后根遍历：
//① 中序遍历第一棵树的子树森林 ② 访问第一棵树的根 ③ 中序遍历其余树构成的森林
void InOrderForest(CSTree T){
    if(T!=NULL){
        InOrderForest(T->firstchild);   //① 中序遍历根结点的子树森林
        visit(T);                       //② 访问第一棵树的根结点
        InOrderForest(T->nextsibling);  //③ 中序遍历其余树构成的森林
    }
}

