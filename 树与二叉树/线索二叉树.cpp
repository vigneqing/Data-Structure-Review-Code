/* ═══════════════════════════════════════════════════════════════════
 * 线索二叉树 (Threaded Binary Tree)
 *
 * 传统二叉链表有 n+1 个空指针，线索二叉树利用它们存放前驱/后继。
 * ltag/rtag=0 → 指向孩子    ltag/rtag=1 → 指向线索
 * ═══════════════════════════════════════════════════════════════════ */

//线索二叉树的存储
typedef struct ThreadNode{
    ElemType data;
    struct ThreadNode *lchild,*rchild;
    int ltag,rtag;
    //左右线索标志 当tag等于0时，表示指向孩子节点，
    // 当tag等于1时，表示指向线索
}ThreadNode,*ThreadTree;


/* ─────────────────────────────────────────
 * 一、二叉树的线索化
 * ───────────────────────────────────────── */

//土方法找中序前驱动
BiTNode *p;
BiTNode *pre=NULL;
ThreadNode *final=NULL;

void InOrder(BiTree T){
    if(T!=NULL){
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

void visit(BiTNode * q){
    if(q==p)
        final = pre;
    else
        pre = q;
}

//中序线索化
typedef struct ThreadNode{
    ElemType data;
    struct ThreadNode *lchild,*rchild;
    int ltag,rtag;
}ThreadNode,*ThreadTree;

ThreadNode *pre=NULL;

void InThread(ThreadTree T){
    if(T!=NULL){
        InThread(T->lchild);
        visit(T);
        InThread(T->rchild);
    }
}

void visit(ThreadNode * q){
    if(q->lchild==NULL){ //左子树为空建立前驱线索
        q->ltag=1;
        q->lchild=pre;
    }
    if(pre!=NULL&&pre->rchild==NULL){
        pre->rtag=1;//前驱结点的后继线索
        pre->rchild=q;
    }
    pre=q;
}

void CreateInThread(ThreadTree T){
    pre=NULL;
    if(T!=NULL){
        InThread(T);//中序线索化
        if(pre->rchild==NULL)
            pre->rtag=1; //最后一个结点的后继线索
    }
}

/* ─── 1.2 中序线索化（书上版本：pre 作为引用参数） ─── */
void InThread(ThreadTree p,ThreadTree &pre){
    if(p!=NULL){
        InThread(p->lchild,pre); //递归线索化左子树
        if(p->lchild==NULL){    //左子树为空建立前驱线索
            p->ltag=1;
            p->lchild=pre;
        }
        if(pre!=NULL&&pre->rchild==NULL){
            pre->rtag=1;    //前驱结点的后继线索
            pre->rchild=p;
        }
        pre=p;  //更新前驱结点
        InThread(p->rchild,pre);//递归线索化右子树
    }
}

/* ─── 1.3 先序线索化 ─── */
//【关键】ltag=0 时才递归左子树，否则 lchild 已是线索会死循环！
void PreThread(ThreadTree T){
    if(T!=NULL){
        visit(T);
        if(T->ltag==0) //注意这里不一样，防止来回切换
            PreThread(T->lchild);
        PreThread(T->rchild);
    }
}

void visit(ThreadNode * q){
    if(q->lchild==NULL){ //左子树为空建立前驱线索
        q->ltag=1;
        q->lchild=pre;
    }
    if(pre!=NULL&&pre->rchild==NULL){
        pre->rtag=1;//前驱结点的后继线索
        pre->rchild=q;
    }
    pre=q;
}

void CreatePreThread(ThreadTree T){
    pre=NULL;
    if(T!=NULL){
        PreThread(T);//中序线索化
        if(pre->rchild==NULL)
            pre->rtag=1; //最后一个结点的后继线索
    }
}

/* ─── 1.4 书上的先序线索化（引用参数版本） ─── */
void PreThread(ThreadTree p,ThreadTree &pre){
    if(p!=NULL){
        if(p->lchild==NULL){    //左子树为空建立前驱线索
            p->ltag=1;
            p->lchild=pre;
        }
        if(pre!=NULL&&pre->rchild==NULL){
            pre->rtag=1;    //前驱结点的后继线索
            pre->rchild=p;
        }
        pre=p;  //更新前驱结点
        if(p->ltag==0)
            PreThread(p->lchild,pre); //递归线索化左子树
        PreThread(p->rchild,pre);//递归线索化右子树
    }
}

/* ─── 1.5 后序线索化 ─── */
typedef struct ThreadNode{
    ElemType data;
    struct ThreadNode *lchild,*rchild;
    int ltag,rtag;
}ThreadNode,*ThreadTree;

ThreadNode *pre=NULL;

void PostThread(ThreadTree T){
    if(T!=NULL){
        PostThread(T->lchild);
        PostThread(T->rchild);
        visit(T);
    }
}

void visit(ThreadNode * q){
    if(q->lchild==NULL){ //左子树为空建立前驱线索
        q->ltag=1;
        q->lchild=pre;
    }
    if(pre!=NULL&&pre->rchild==NULL){
        pre->rtag=1;//前驱结点的后继线索
        pre->rchild=q;
    }
    pre=q;
}

void CreatePostThread(ThreadTree T){
    pre=NULL;
    if(T!=NULL){
        PostThread(T);//中序线索化
        if(pre->rchild==NULL)
            pre->rtag=1; //最后一个结点的后继线索
    }
}

/* ─── 1.6 书上的后序线索化（引用参数版本） ─── */
void InThread(ThreadTree p,ThreadTree &pre){
    if(p!=NULL){
        PostThread(p->lchild,pre); //递归线索化左子树
        PostThread(p->rchild,pre);//递归线索化右子树
        if(p->lchild==NULL){    //左子树为空建立前驱线索
            p->ltag=1;
            p->lchild=pre;
        }
        if(pre!=NULL&&pre->rchild==NULL){
            pre->rtag=1;    //前驱结点的后继线索
            pre->rchild=p;
        }
        pre=p;  //更新前驱结点
    }
}


/* ═══════════════════════════════════════════════════════════════════
 * 二、中序线索二叉树 —— 找前驱与后继
 * ═══════════════════════════════════════════════════════════════════ */

/* ─── 2.1 找中序后继（正向遍历） ─── */
//找到以P为根的子树中，第一个被中序遍历的结点（最左下结点）
ThreadNode *Firstnode(ThreadNode * p){
    while(p->ltag==0) p=p->lchild;
    return p;
}

//在中序线索二叉树中找到结点p的后继结点
ThreadNode *Nextnode(ThreadNode * p){
    if(p->rtag==0) return Firstnode(p->rchild);
    else return p->rchild;
}

//对中序线索二叉树进行中序遍历
void Inorder(ThreadTree *T){
    for(ThreadNode *p=Firstnode(*T);p!=NULL;p=Nextnode(p))
        visit(p);
}

/* ─── 2.2 找中序前驱（逆向遍历） ─── */
//找到以P为根的子树中，最后一个被中序遍历的结点（最右下结点）
ThreadNode *Lastnode(ThreadNode * p){
    while(p->rtag==0) p=p->rchild;
    return p;
}

//在中序线索二叉树中找到结点p的后继结点
ThreadNode *Prenode(ThreadNode * p){
    if(p->ltag==0) return Lastnode(p->lchild);
    else return p->lchild;
}

//对中序线索二叉树进行逆中序遍历
void RevInorder(ThreadTree *T){
    for(ThreadNode *p=Lastnode(*T);p!=NULL;p=Prenode(p))
        visit(p);
}


/* ═══════════════════════════════════════════════════════════════════
 * 三、先序线索二叉树 —— 找后继
 *
 * 先序: 根→左→右
 * 有左孩子 → 后继=左孩子
 * 无左孩子 → 后继=rchild(无论rtag，右孩子或线索都是后继)
 * ═══════════════════════════════════════════════════════════════════ */

// 在先序线索二叉树中找到结点p的后继结点
ThreadNode *PreNextnode(ThreadNode *p){
    if(p->ltag==0)                  // 有左孩子,后继就是左孩子(根→左)
        return p->lchild;
    else                            // 左孩子是线索(无左孩子)
        return p->rchild;           // rtag=0时右孩子是后继,rtag=1时rchild指向后继线索
}

// 对先序线索二叉树进行先序遍历(利用后继)
void PreOrderTraverse(ThreadTree T){
    for(ThreadNode *p=T;p!=NULL;p=PreNextnode(p))
        visit(p);
}


/* ═══════════════════════════════════════════════════════════════════
 * 四、后序线索二叉树 —— 找前驱
 *
 * 后序: 左→右→根
 * 有右孩子 → 前驱=右孩子
 * 无右孩子 → 前驱=lchild(无论ltag，左孩子或线索都是前驱)
 * ═══════════════════════════════════════════════════════════════════ */

// 在后序线索二叉树中找到结点p的前驱结点
ThreadNode *PostPrenode(ThreadNode *p){
    if(p->rtag==0)                  // 有右孩子,前驱就是右孩子(右子树最后访问完才到根)
        return p->rchild;
    else                            // 右孩子是线索(无右孩子)
        return p->lchild;           // ltag=0时左孩子是前驱,ltag=1时lchild指向前驱线索
}

// 对后序线索二叉树进行逆后序遍历(即从最后一个结点向前找前驱)
void RevPostOrderTraverse(ThreadTree T){
    // 后序最后一个结点就是根节点,从根开始不断找前驱即是逆后序
    for(ThreadNode *p=T;p!=NULL;p=PostPrenode(p))
        visit(p);
}


/* ═══════════════════════════════════════════════════════════════════
 * 五、三叉链表 —— 解决"找另一边"难题
 *
 * 先序找前驱 / 后序找后继 无法直接从线索获得，需借助 parent 指针。
 * 三叉链表 = 线索二叉树 + parent 指针
 * ═══════════════════════════════════════════════════════════════════ */

// 三叉链表结点: 在二叉线索链表基础上增加parent指针指向父节点
typedef struct TriThreadNode{
    ElemType data;
    struct TriThreadNode *lchild,*rchild,*parent;
    int ltag,rtag;
}TriThreadNode,*TriThreadTree;

/* ─── 5.1 先序找前驱 ─── */
/*
 * 有左孩子(ltag=0)时需回溯父节点，分四种情况：
 * ① ltag=1 → lchild 即前驱
 * ② p 是左孩子 → parent 即前驱
 * ③ p 是右孩子 & parent有左 → 左子树先序末结点
 * ④ p 是右孩子 & parent无左 → parent 即前驱
 */
// 先序: 根 → 左 → 右
// 寻找以p为根的子树中,先序遍历的最后一个结点(最右下的叶子)
// 有右走右,无右走左,直到叶子
TriThreadNode *PreLastNode(TriThreadNode *p){
    while(p->ltag==0 || p->rtag==0){    // 还有孩子
        if(p->rtag==0)                  // 优先走右孩子
            p=p->rchild;
        else                            // 无右孩子则走左孩子
            p=p->lchild;
    }
    return p;
}

// 在三叉链表的先序线索二叉树中找到结点p的前驱
TriThreadNode *TriPrePrenode(TriThreadNode *p){
    if(p->ltag==1)                      // 左孩子是线索,直接指向前驱
        return p->lchild;
    else{                               // p有左孩子,需要借助父节点找前驱
        TriThreadNode *parent=p->parent;
        if(parent==NULL)                // p是根节点,无前驱
            return NULL;
        if(p==parent->rchild){          // p是父节点的右孩子
            // 若父节点有左孩子,前驱是父节点左子树先序的最后一个结点
            if(parent->ltag==0)
                return PreLastNode(parent->lchild);
            else                        // 父节点无左孩子,前驱就是父节点
                return parent;
        }else{                          // p是父节点的左孩子
            return parent;              // 前驱就是父节点(根→左)
        }
    }
}

// 对三叉先序线索二叉树进行逆先序遍历(不断找前驱)
void TriRevPreOrder(TriThreadTree T){
    // 先找到先序遍历的最后一个结点
    TriThreadNode *p=PreLastNode(T);
    for(;p!=NULL;p=TriPrePrenode(p))
        visit(p);
}

/* ─── 5.2 后序找后继 ─── */
/*
 * 有右孩子(rtag=0)时需回溯父节点，分四种情况：
 * ① rtag=1 → rchild 即后继
 * ② p 是右孩子 → parent 即后继
 * ③ p 是左孩子 & parent有右 → 右子树后序首结点
 * ④ p 是左孩子 & parent无右 → parent 即后继
 */
// 后序: 左 → 右 → 根
// 寻找以p为根的子树中,后序遍历的第一个结点(最左下的叶子)
// 有左走左,无左走右,直到叶子
TriThreadNode *PostFirstNode(TriThreadNode *p){
    while(p->ltag==0 || p->rtag==0){    // 还有孩子
        if(p->ltag==0)                  // 优先走左孩子
            p=p->lchild;
        else                            // 无左孩子则走右孩子
            p=p->rchild;
    }
    return p;
}

// 在三叉链表的后序线索二叉树中找到结点p的后继
TriThreadNode *TriPostNextnode(TriThreadNode *p){
    if(p->rtag==1)                      // 右孩子是线索,直接指向后继
        return p->rchild;
    else{                               // p有右孩子,需要借助父节点找后继
        TriThreadNode *parent=p->parent;
        if(parent==NULL)                // p是根节点,无后继
            return NULL;
        if(p==parent->lchild){          // p是父节点的左孩子
            // 若父节点有右孩子,后继是父节点右子树后序的第一个结点
            if(parent->rtag==0)
                return PostFirstNode(parent->rchild);
            else                        // 父节点无右孩子,后继就是父节点
                return parent;
        }else{                          // p是父节点的右孩子
            return parent;              // 后继就是父节点(右→根)
        }
    }
}

// 对三叉后序线索二叉树进行后序遍历(不断找后继)
void TriPostOrderTraverse(TriThreadTree T){
    // 先找到后序遍历的第一个结点
    TriThreadNode *p=PostFirstNode(T);
    for(;p!=NULL;p=TriPostNextnode(p))
        visit(p);
}

