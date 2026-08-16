/* ═══════════════════════════════════════════════════════════════════
 * 查找算法与平衡二叉树
 * ═══════════════════════════════════════════════════════════════════ */

/* ─────────────────────────────────────────
 * 一、顺序查找
 * ───────────────────────────────────────── */

//顺序查找表的定义：存储空间连续，查找依次比较
//表长 TableLen 表示元素个数
//元素下标从 0 开始存储
typedef struct {
    Elemtype *elem;
    int TableLen;
}SSTable;

//顺序查找：从前往后扫描，找到返回下标，否则返回 -1
int Serch_Seq(SSTable ST, Elemtype key) {
    int i;
    for (i=0;i<ST.TanbleLen && ST.elem[i]!=key;++i);
    //查找成功则返回元素下标，否则返回-1
    return i==ST.TableLen?-1:i;
}

//哨兵顺序查找：将 key 放在数组第 0 位作为哨兵，
//这样不需要额外判断是否越界，适合“数据下标从 1 开始存”的写法
int Serch_Seq(SSTable ST, Elemtype key) {
    ST.elem[0]=key;
    int i;
    for (i=ST.TableLen;ST.elem[i]!=key;--i);
    //查找成功则返回元素下标，否则返回0
    return i;
}

//顺序查找优化：将顺序表按升序排序后，可利用“有序性”进行优化
//例如：先比较大小，再决定是否继续查找

/* ─────────────────────────────────────────
 * 二、折半查找（二分查找）
 * ───────────────────────────────────────── */

//折半查找（二分查找），仅适用于有序的顺序表
//每次将查找区间缩小一半，时间复杂度为 O(log n)
int Binary_Search(SSTable L, Elemtype key){
    int low=0,high=L.TableLen-1,mid;
    while(low<=high){
        mid=(low+high)/2;
        if(key==L.elem[mid])
            return mid;
        else if(key<L.elem[mid])
            high=mid-1;
        else
            low=mid+1;
    }
    return -1;
}

/* ─────────────────────────────────────────
 * 三、分块查找
 * ───────────────────────────────────────── */

//分块查找：将表分成多个块，并在块中建立索引
//索引表用于存放每块最大值和块的范围
//索引表
typedef struct {
    Elemtype maxValue;
    int low,high;
}Index;
//实际存储元素
Elemtype List[100];

/* ─────────────────────────────────────────
 * 四、二叉排序树（BST）
 * ───────────────────────────────────────── */

//二叉排序树查找：遵循左小右大规则
//若 key 小于当前结点，则向左子树查找；反之向右子树查找
typedef struct BSTNode{
    int key;
    struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;

BSTNode *BST_Search(BSTree T,int key){
    while(T!=NULL && T->key!=key){\
       if(key<T->key)
            T=T->lchild;
        else
            T=T->rchild;
    }
    return T;
}

//递归方式
BSTNode *BST_Search(BSTree T,int key){
    if(T==NULL)
        return NULL;
    if(key==T->key)
        return T;
    else if(key<T->key)
        return BST_Search(T->lchild,key);
    else
        return BST_Search(T->rchild,key);
}

//二叉排序树的插入
int BST_Insert(BSTree &T,int k){
    if(T==NULL){
        T=(BSTree)malloc(sizeof(BSTNode));
        T->key=k;
        T->lchild=NULL;
        T->rchild=NULL;
        return 1;
    }
    else if(k==T->key)
        return 0;
    else if(k<T->key)
        return BST_Insert(T->lchild,k);
    else
        return BST_Insert(T->rchild,k);
}

//二叉排序树的构造：依次插入 n 个关键字，可得到一棵二叉排序树
void Create_BST(BSTree &T,int str[],int n){
    T=NULL;
    int i=0;
    while(i<n){
        BST_Insert(T,str[i]);
        i++;
    }
}

/* ─────────────────────────────────────────
 * 五、平衡二叉树（AVL树）
 * ───────────────────────────────────────── */

//平衡二叉树的结点：balance 表示平衡因子
//balance = 左子树高度 - 右子树高度
//当 |balance| <= 1 时，树保持平衡
//树节点
typedef struct AVLNode{
    int key;
    int balance;
    struct AVLNode *lchild,*rchild;
}AVLNode,*AVLTree;


// 二叉排序树删除：删除结点后仍保持二叉排序树性质
// 采用“前驱/后继替换法”，适用于删除度为2的结点
BSTNode *BST_MinNode(BSTree T){
    while(T!=NULL && T->lchild!=NULL)
        T=T->lchild;
    return T;
}

BSTree BST_Delete(BSTree &T, int key){
    if(T==NULL)
        return NULL;

    if(key < T->key)
        T->lchild = BST_Delete(T->lchild, key);
    else if(key > T->key)
        T->rchild = BST_Delete(T->rchild, key);
    else{
        // 1. 叶子结点
        if(T->lchild==NULL && T->rchild==NULL){
            free(T);
            T = NULL;
        }
        // 2. 只有左子树
        else if(T->lchild!=NULL && T->rchild==NULL){
            BSTNode *temp = T;
            T = T->lchild;
            free(temp);
        }
        // 3. 只有右子树
        else if(T->lchild==NULL && T->rchild!=NULL){
            BSTNode *temp = T;
            T = T->rchild;
            free(temp);
        }
        // 4. 左右子树都存在：用右子树中的最小结点替代
        else{
            BSTNode *minNode = BST_MinNode(T->rchild);
            T->key = minNode->key;
            T->rchild = BST_Delete(T->rchild, minNode->key);
        }
    }
    return T;
}

//====================================================
// AVL平衡二叉树：高度/平衡因子计算与旋转
//====================================================

// 计算树高
int AVL_Height(AVLTree T){
    if(T==NULL)
        return 0;
    int leftH = AVL_Height(T->lchild);
    int rightH = AVL_Height(T->rchild);
    return leftH > rightH ? leftH + 1 : rightH + 1;
}

// 更新平衡因子
void AVL_UpdateBalance(AVLTree T){
    if(T==NULL)
        return;
    T->balance = AVL_Height(T->lchild) - AVL_Height(T->rchild);
}

// LL：右单旋转
AVLTree AVL_RotateRight(AVLTree T){
    AVLNode *temp = T->lchild;
    T->lchild = temp->rchild;
    temp->rchild = T;
    AVL_UpdateBalance(T);
    AVL_UpdateBalance(temp);
    return temp;
}

// RR：左单旋转
AVLTree AVL_RotateLeft(AVLTree T){
    AVLNode *temp = T->rchild;
    T->rchild = temp->lchild;
    temp->lchild = T;
    AVL_UpdateBalance(T);
    AVL_UpdateBalance(temp);
    return temp;
}

// LR：先左后右双旋转
AVLTree AVL_RotateLeftRight(AVLTree T){
    T->lchild = AVL_RotateLeft(T->lchild);
    return AVL_RotateRight(T);
}

// RL：先右后左双旋转
AVLTree AVL_RotateRightLeft(AVLTree T){
    T->rchild = AVL_RotateRight(T->rchild);
    return AVL_RotateLeft(T);
}

// AVL树插入：递归插入，插入后自底向上调整平衡
void AVL_Insert(AVLTree &T, int key){
    if(T==NULL){
        T = (AVLTree)malloc(sizeof(AVLNode));
        T->key = key;
        T->balance = 0;
        T->lchild = NULL;
        T->rchild = NULL;
        return;
    }

    if(key < T->key)
        AVL_Insert(T->lchild, key);
    else if(key > T->key)
        AVL_Insert(T->rchild, key);
    else
        return;  // 已存在，插入失败

    AVL_UpdateBalance(T);

    // 失衡处理
    if(T->balance == 2){
        // LL 或 LR
        if(AVL_Height(T->lchild->lchild) >= AVL_Height(T->lchild->rchild))
            T = AVL_RotateRight(T);
        else
            T = AVL_RotateLeftRight(T);
    }
    else if(T->balance == -2){
        // RR 或 RL
        if(AVL_Height(T->rchild->rchild) >= AVL_Height(T->rchild->lchild))
            T = AVL_RotateLeft(T);
        else
            T = AVL_RotateRightLeft(T);
    }

    AVL_UpdateBalance(T);
}

// AVL树删除：递归删除结点，并在删除后继续平衡
AVLTree AVL_Delete(AVLTree &T, int key){
    if(T==NULL)
        return NULL;

    if(key < T->key)
        T->lchild = AVL_Delete(T->lchild, key);
    else if(key > T->key)
        T->rchild = AVL_Delete(T->rchild, key);
    else{
        // 叶子结点
        if(T->lchild==NULL && T->rchild==NULL){
            free(T);
            return NULL;
        }
        // 只有左子树
        if(T->lchild!=NULL && T->rchild==NULL){
            AVLNode *temp = T->lchild;
            free(T);
            return temp;
        }
        // 只有右子树
        if(T->lchild==NULL && T->rchild!=NULL){
            AVLNode *temp = T->rchild;
            free(T);
            return temp;
        }

        // 两个子树都存在：用右子树中的最小值替换
        AVLNode *minNode = T->rchild;
        while(minNode->lchild != NULL)
            minNode = minNode->lchild;

        T->key = minNode->key;
        T->rchild = AVL_Delete(T->rchild, minNode->key);
    }

    AVL_UpdateBalance(T);

    if(T!=NULL && T->balance == 2){
        if(AVL_Height(T->lchild->lchild) >= AVL_Height(T->lchild->rchild))
            T = AVL_RotateRight(T);
        else
            T = AVL_RotateLeftRight(T);
    }
    else if(T!=NULL && T->balance == -2){
        if(AVL_Height(T->rchild->rchild) >= AVL_Height(T->rchild->lchild))
            T = AVL_RotateLeft(T);
        else
            T = AVL_RotateRightLeft(T);
    }

    if(T!=NULL)
        AVL_UpdateBalance(T);

    return T;
}

//====================================================
// 备注：
// 1. 二叉排序树查找/插入/删除的时间复杂度平均为 O(log n)，最坏为 O(n)
// 2. AVL树通过旋转保持平衡，查找、插入、删除平均时间复杂度为 O(log n)
// 3. 散列表查找平均时间复杂度为 O(1)，但最坏可能退化到 O(n)
// 4. 结构体命名与具体题目要求一致时，可以把上述实现按需改为你原有的类型名
//====================================================
