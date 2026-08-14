/* ═══════════════════════════════════════════════════════════════════
 * 图 (Graph)
 * ─────────────────────────────────────────────────────────────────
 * 图的存储结构：邻接矩阵 / 邻接表 / 十字链表 / 邻接多重表
 * 图的基本操作：建立、插入、删除、查找、遍历
 * 图的遍历：广度优先遍历（BFS）/ 深度优先遍历（DFS）
 * ═══════════════════════════════════════════════════════════════════ */

/* ─────────────────────────────────────────
 * 一、邻接矩阵法（顺序存储）
 * 适用场景：适合稠密图，顶点数较少、边数较多的情况
 * 特点：矩阵中任意两点间是否存在边可直接访问，时间复杂度为 O(1)
 * 缺点：空间复杂度为 O(V^2)，对稀疏图会造成较大浪费
 * ───────────────────────────────────────── */

#define MaxVertexNum 100
//可以用int的最大值表示无穷
#define INFINITY
typedef struct {
    char Vex[MaxVertexNum]; //顶点信息
    int Edge[MaxVertexNum][MaxVertexNum]; //边信息
    int vexnum, arcnum; //顶点数和边数
} MGraph;

/* ─────────────────────────────────────────
 * 二、邻接表法（链式存储）
 * 适用场景：适合稀疏图，顶点数较多但边数相对较少的情况
 * 特点：每个顶点对应一条链表，存储所有与该顶点相邻的边
 * 优点：空间复杂度更低，尤其适合考研图论题目
 * ───────────────────────────────────────── */

//邻接表法
//边结点：记录当前顶点的一个邻接顶点及其后继指针
typedef struct ArcNode {
    int adjvex; //邻接顶点编号
    struct ArcNode *next; //指向下一条邻接边
} ArcNode;

//顶点结点：存储顶点数据和指向第一条边的指针
typedef struct VNode {
    VertexType data; //顶点信息
    ArcNode *first; //指向第一条邻接边
} VNode,AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices; //邻接表数组
    int vexnum, arcnum; //顶点数和边数
} ALGraph;

/* ─────────────────────────────────────────
 * 三、十字链表法（有向图）
 * 适用场景：主要用于有向图的存储与运算
 * 特点：同时保存入边和出边，便于求顶点的入度和出度
 * ───────────────────────────────────────── */

//十字链表法（有向图）
//弧结点：用于保存有向边的起点、终点及双向链关系
typedef struct ArcBox {
    int tailvex, headvex; //弧尾顶点编号、弧头顶点编号
    struct ArcBox *hlink, *tlink; //分别指向同头结点、同尾结点的下一条弧
} ArcBox;

//顶点结点：保存顶点信息，并分别指向第一条入弧和出弧
typedef struct VexNode2 {
    VertexType data; //顶点信息
    ArcBox *firstin, *firstout; //指向第一条入弧和第一条出弧
} VexNode2;

typedef struct {
    VexNode2 xlist[MaxVertexNum]; //顶点数组
    int vexnum, arcnum; //顶点数和弧数
} OLGraph;

/* ─────────────────────────────────────────
 * 四、邻接多重表法（无向图）
 * 适用场景：适合无向图的边存储，并且需要高效删除边
 * 特点：每条边只存一次，且每个顶点维护依附于它的边链表
 * ───────────────────────────────────────── */

//邻接多重表法（无向图）
//边结点：记录一条无向边所依附的两个顶点及其对应链指针
typedef struct ArcNode2 {
    int ivex, jvex; //边依附的两个顶点编号
    struct ArcNode2 *ilink, *jlink; //分别指向依附于 ivex 和 jvex 的下一条边
} ArcNode2;

//顶点结点：保存顶点信息和该顶点所连接的第一条边
typedef struct VNode2 {
    VertexType data; //顶点信息
    ArcNode2 *firstedge; //指向第一条依附于该顶点的边
} VNode2;

typedef struct {
    VNode2 adjmulist[MaxVertexNum]; //顶点数组
    int vexnum, arcnum; //顶点数和边数
} AMLGraph;

/* ─────────────────────────────────────────
 * 五、图的基本操作
 * 说明：图的基本操作需根据图的类型和存储方式决定具体实现方式
 * ───────────────────────────────────────── */

//图的基本操作
//图的基本操作跟图的类型以及图的存储方式有关

/* ─────────────────────────────────────────
 * 六、图的遍历算法
 * ───────────────────────────────────────── */

//广度优先遍历（Breadth-First Search，BFS）
//思想：从某个起点出发，先访问其所有邻接点，再依次访问下一层顶点
bool visited[Max_Vertex_Num] //访问标记数组，初始设为 false
void BFSTraverse(Graph G){
    for (i = 0; i < G.vexnum; ++i) {
        visited[i] = false; // 初始化访问标记数组
    }
    InitQueue(Q); // 初始化队列
    for (i = 0; i < G.vexnum; ++i) {
       if (!visited[i])
           BFS(G, i); // 对每个连通分量做一次广度优先搜索
    }
}

void BFS(Graph G, int v) {
    visit[v]; // 访问顶点 v
    visited[v] = true; // 标记顶点 v 已访问
    Enqueue(Q, v); // 将顶点 v 入队
    while (!isEmpty(Q)) {
        DeQueue(Q, v); // 队头顶点出队，作为当前访问顶点
        for (w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!visited[w]) {
                visit[w]; // 访问顶点 w
                visited[w] = true; // 标记顶点 w 已访问
                Enqueue(Q, w); // 将顶点 w 入队
            }
        }
    }
}

//深度优先遍历（Depth-First Search，DFS）
//思想：从某个起点出发，沿着一条路径一直往下走，直到不能继续再回溯
bool visited[Max_Vertex_Num] //访问标记数组，初始设为 false
void DFSTraverse(Graph G){
    for (v = 0; v < G.vexnum; ++v) {
        visited[v] = false; // 初始化访问标记数组
    }
    for (v = 0; v < G.vexnum; ++v) {
      if (!visited[v])
          DFS(G, v); // 对每个连通分量做一次深度优先搜索
    }
}
void DFS(Graph G, int v) {
    visit[v]; // 访问顶点 v
    visited[v] = true; // 标记顶点 v 已访问
    for (w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w]) {
            DFS(G, w); // 递归调用 DFS，对顶点 w 继续深度优先搜索
        }
    }
}

/*
 * 图的补充说明：
 * 1. 邻接矩阵适合稠密图，访问边的时间复杂度通常为 O(1)；
 * 2. 邻接表适合稀疏图，空间复杂度更低，常用于考试与算法题中；
 * 3. BFS 适合求最短路径和无权图中的层次遍历；
 * 4. DFS 适合求连通分量、回溯搜索和拓扑相关问题；
 * 5. 图的存储方式不同，遍历时需根据具体结构实现 FirstNeighbor 和 NextNeighbor。
 */
