/* ═══════════════════════════════════════════════════════════════════
 * 红黑树与 B 树
 * ═══════════════════════════════════════════════════════════════════ */

// 说明：红黑树是满足特定性质的平衡二叉搜索树，
// 其查找、插入、删除的时间复杂度均为 O(log n)

#include <cstdlib>

typedef int Elemtype;

enum { RED = 0, BLACK = 1 };

/* ─────────────────────────────────────────
 * 一、红黑树结点结构
 * ───────────────────────────────────────── */

struct RBNode {
    int key;
    RBNode *parent;
    RBNode *lchild;
    RBNode *rchild;
    int color;
};

typedef RBNode *RBTree;

/* ─────────────────────────────────────────
 * 二、红黑树查找
 * ───────────────────────────────────────── */

//红黑树的查找：类似普通二叉搜索树，按 key 与结点值比较
RBNode *RB_Search(RBTree T, int key) {
    while (T != NULL && T->key != key) {
        if (key < T->key)
            T = T->lchild;
        else
            T = T->rchild;
    }
    return T;
}

/* ─────────────────────────────────────────
 * 三、红黑树插入
 * ───────────────────────────────────────── */

// 左旋转：使 x 的右孩子成为当前子树的新根
void RB_LeftRotate(RBTree &T, RBNode *x) {
    RBNode *y = x->rchild;
    if (y == NULL)
        return;

    x->rchild = y->lchild;
    if (y->lchild != NULL)
        y->lchild->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        T = y;
    else if (x == x->parent->lchild)
        x->parent->lchild = y;
    else
        x->parent->rchild = y;

    y->lchild = x;
    x->parent = y;
}

void RB_RightRotate(RBTree &T, RBNode *y) {
    RBNode *x = y->lchild;
    if (x == NULL)
        return;

    y->lchild = x->rchild;
    if (x->rchild != NULL)
        x->rchild->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL)
        T = x;
    else if (y == y->parent->lchild)
        y->parent->lchild = x;
    else
        y->parent->rchild = x;

    x->rchild = y;
    y->parent = x;
}

void RB_InsertFixUp(RBTree &T, RBNode *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        RBNode *p = z->parent;
        RBNode *g = p->parent;

        if (p == g->lchild) {
            RBNode *uncle = g->rchild;
            if (uncle != NULL && uncle->color == RED) {
                p->color = BLACK;
                uncle->color = BLACK;
                g->color = RED;
                z = g;
            } else {
                if (z == p->rchild) {
                    z = p;
                    RB_LeftRotate(T, z);
                    p = z->parent;
                }
                p->color = BLACK;
                g->color = RED;
                RB_RightRotate(T, g);
            }
        } else {
            RBNode *uncle = g->lchild;
            if (uncle != NULL && uncle->color == RED) {
                p->color = BLACK;
                uncle->color = BLACK;
                g->color = RED;
                z = g;
            } else {
                if (z == p->lchild) {
                    z = p;
                    RB_RightRotate(T, z);
                    p = z->parent;
                }
                p->color = BLACK;
                g->color = RED;
                RB_LeftRotate(T, g);
            }
        }
    }
    T->color = BLACK;
}

void RB_Insert(RBTree &T, int key) {
    RBNode *z = new RBNode();
    z->key = key;
    z->parent = NULL;
    z->lchild = NULL;
    z->rchild = NULL;
    z->color = RED;

    RBNode *y = NULL;
    RBNode *x = T;

    while (x != NULL) {
        y = x;
        if (key < x->key)
            x = x->lchild;
        else
            x = x->rchild;
    }

    z->parent = y;
    if (y == NULL)
        T = z;
    else if (key < y->key)
        y->lchild = z;
    else
        y->rchild = z;

    RB_InsertFixUp(T, z);
}

/* ─────────────────────────────────────────
 * 四、红黑树删除
 * ───────────────────────────────────────── */

// 用 v 替换 u 的位置，保持树结构连续性
void RB_Transplant(RBTree &T, RBNode *u, RBNode *v) {
    if (u->parent == NULL)
        T = v;
    else if (u == u->parent->lchild)
        u->parent->lchild = v;
    else
        u->parent->rchild = v;

    if (v != NULL)
        v->parent = u->parent;
}

RBNode *RB_MinNode(RBTree T) {
    while (T != NULL && T->lchild != NULL)
        T = T->lchild;
    return T;
}

void RB_DeleteFixUp(RBTree &T, RBNode *x, RBNode *parent) {
    while ((x == NULL || x->color == BLACK) && x != T) {
        if (x == parent->lchild) {
            RBNode *w = parent->rchild;
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                RB_LeftRotate(T, parent);
                w = parent->rchild;
            }

            if ((w->lchild == NULL || w->lchild->color == BLACK) &&
                (w->rchild == NULL || w->rchild->color == BLACK)) {
                w->color = RED;
                x = parent;
                parent = x->parent;
            } else {
                if (w->rchild == NULL || w->rchild->color == BLACK) {
                    if (w->lchild != NULL)
                        w->lchild->color = BLACK;
                    w->color = RED;
                    RB_RightRotate(T, w);
                    w = parent->rchild;
                }
                w->color = parent->color;
                parent->color = BLACK;
                if (w->rchild != NULL)
                    w->rchild->color = BLACK;
                RB_LeftRotate(T, parent);
                x = T;
            }
        } else {
            RBNode *w = parent->lchild;
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                RB_RightRotate(T, parent);
                w = parent->lchild;
            }

            if ((w->lchild == NULL || w->lchild->color == BLACK) &&
                (w->rchild == NULL || w->rchild->color == BLACK)) {
                w->color = RED;
                x = parent;
                parent = x->parent;
            } else {
                if (w->lchild == NULL || w->lchild->color == BLACK) {
                    if (w->rchild != NULL)
                        w->rchild->color = BLACK;
                    w->color = RED;
                    RB_LeftRotate(T, w);
                    w = parent->lchild;
                }
                w->color = parent->color;
                parent->color = BLACK;
                if (w->lchild != NULL)
                    w->lchild->color = BLACK;
                RB_RightRotate(T, parent);
                x = T;
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}

void RB_Delete(RBTree &T, int key) {
    RBNode *z = RB_Search(T, key);
    if (z == NULL)
        return;

    RBNode *y = z;
    RBNode *x = NULL;
    RBNode *xParent = NULL;
    int yOriginalColor = y->color;

    if (z->lchild == NULL) {
        x = z->rchild;
        xParent = z->parent;
        RB_Transplant(T, z, z->rchild);
    } else if (z->rchild == NULL) {
        x = z->lchild;
        xParent = z->parent;
        RB_Transplant(T, z, z->lchild);
    } else {
        y = RB_MinNode(z->rchild);
        yOriginalColor = y->color;
        x = y->rchild;
        xParent = y->parent;
        if (y->parent == z) {
            xParent = y;
        }
        if (y->parent != z) {
            RB_Transplant(T, y, y->rchild);
            y->rchild = z->rchild;
            y->rchild->parent = y;
        }
        RB_Transplant(T, z, y);
        y->lchild = z->lchild;
        y->lchild->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK)
        RB_DeleteFixUp(T, x, xParent);

    delete z;
}

/* ─────────────────────────────────────────
 * 五、B 树（多路查找树）
 * ───────────────────────────────────────── */

// eg五叉查找树：一个结点最多 4 个关键字，最多 5 个孩子
// 这是 B 树的典型表示思路之一
struct Node {
    Elemtype keys[4];
    struct Node *child[5];
    int num;
};

//B树的查找：在结点内顺序查找，再按区间走向子树
Node *B_Search(Node *T, Elemtype key) {
    if (T == NULL)
        return NULL;

    int i = 0;
    while (i < T->num && key > T->keys[i])
        ++i;

    if (i < T->num && key == T->keys[i])
        return T;

    if (T->child[0] == NULL)
        return NULL;

    return B_Search(T->child[i], key);
}

/* ─────────────────────────────────────────
 * 六、B 树插入
 * ───────────────────────────────────────── */

//B树的插入：若结点已满，则先分裂，再插入关键字
void B_Insert(Node *&T, Elemtype key) {
    if (T == NULL) {
        T = new Node();
        T->num = 1;
        T->keys[0] = key;
        for (int i = 0; i < 5; ++i)
            T->child[i] = NULL;
        return;
    }

    // 结点已满，先分裂再插入
    if (T->num == 4) {
        Node *newNode = new Node();
        newNode->num = 0;
        for (int i = 0; i < 5; ++i)
            newNode->child[i] = NULL;

        for (int i = 0; i < 2; ++i)
            newNode->keys[i] = T->keys[i + 2];
        newNode->num = 2;

        for (int i = 0; i < 2; ++i)
            newNode->child[i] = T->child[i + 3];

        for (int i = 0; i < 2; ++i)
            T->keys[i + 2] = 0;
        T->num = 2;

        Node *root = T;
        T = new Node();
        T->num = 1;
        T->keys[0] = root->keys[2];
        T->child[0] = root;
        T->child[1] = newNode;
        for (int i = 2; i < 5; ++i)
            T->child[i] = NULL;
    }

    int i = 0;
    while (i < T->num && key > T->keys[i])
        ++i;

    if (T->child[0] != NULL && i < T->num && key == T->keys[i])
        return;

    if (T->child[0] != NULL && key != T->keys[i]) {
        B_Insert(T->child[i], key);
        return;
    }

    for (int j = T->num; j > i; --j)
        T->keys[j] = T->keys[j - 1];

    T->keys[i] = key;
    T->num++;
}

/* ─────────────────────────────────────────
 * 七、B 树删除
 * ───────────────────────────────────────── */

//B树的删除：若结点中存在 key，则删除；
//若该结点还有子树，则用前驱/后继进行调整
void B_Delete(Node *&T, Elemtype key) {
    if (T == NULL)
        return;

    int i = 0;
    while (i < T->num && key > T->keys[i])
        ++i;

    if (i < T->num && key == T->keys[i]) {
        if (T->child[0] == NULL) {
            for (int j = i; j < T->num - 1; ++j)
                T->keys[j] = T->keys[j + 1];
            T->num--;
            return;
        }

        Node *left = T->child[i];
        Node *right = T->child[i + 1];
        T->keys[i] = left->keys[left->num - 1];
        B_Delete(left, left->keys[left->num - 1]);
        return;
    }

    if (T->child[0] != NULL)
        B_Delete(T->child[i], key);
}

//====================================================
// 备注：
// 1. 红黑树：满足“根黑、红结点子结点必须为黑、任一路径黑高相同”
// 2. 查找平均复杂度为 O(log n)，插入/删除均为 O(log n)
// 3. B树/多路搜索树适合外存数据结构，节点关键字较多，查找稳定在 O(log n)
// 4. 这份代码可直接作为考研笔记模板，具体题目可按需替换 Elemtype / key 类型
//====================================================

