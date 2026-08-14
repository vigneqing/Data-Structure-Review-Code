/* ═══════════════════════════════════════════════════════════════════
 * 拓扑排序 (Topological Sort)
 * ─────────────────────────────────────────────────────────────────
 * 适用范围：有向无环图（DAG）
 * 核心思想：每次选择入度为 0 的顶点，输出后删除其所有出边，
 *          直到所有顶点都被处理完，得到一个合法的拓扑序列
 * ═══════════════════════════════════════════════════════════════════ */

#define MaxVertexNum 100 // 顶点数最大值

// 边表结点：存放一条有向边所指向的邻接顶点
typedef struct ArcNode {
    int adjvex;               // 该弧所指向的顶点
    struct ArcNode *nextarc;  // 指向下一条弧的指针
    // InfoType info;        // 网的边权值
} ArcNode;

// 顶点表结点：存放顶点信息和第一条出边指针
typedef struct VNode {
    VertexType data;       // 顶点信息
    ArcNode *firstarc;     // 指向第一条弧的指针
} VNode, AdjList[MaxVertexNum];

// 图的邻接表表示
typedef struct {
    AdjList vertices;   // 邻接表
    int vexnum, arcnum; // 顶点数和边数
} Graph;

/* ─────────────────────────────────────────
 * 拓扑排序算法
 * 说明：采用栈来保存当前所有入度为 0 的顶点。
 * 每次弹出一个入度为 0 的顶点，并更新其邻接顶点的入度。
 * ───────────────────────────────────────── */
bool TopologicalSort(Graph G) {
    InitStack S; // 初始化栈，存储入度为 0 的顶点
    for (int i = 0; i < G.vexnum; i++)
        if (indegree[i] == 0)
            Push(S, i); // 将入度为 0 的顶点入栈

    int count = 0; // 计数器，记录拓扑序列中的顶点个数
    while (!isEmpty(S)) { // 栈不空时说明仍有入度为 0 的顶点
        Pop(S, i); // 弹出栈顶元素
        print[count++] = i; // 记录拓扑序列
        for (p = G.vertices[i].firstarc; p; p = p->nextarc) {
            // 依次遍历顶点 i 的所有邻接顶点，减小其入度
            // 若某顶点入度减为 0，则将该顶点加入栈中
            v = p->adjvex;
            if (!--indegree[v])
                Push(S, v);
        }
    }

    if (count < G.vexnum)
        return false; // 图中存在环，无法进行拓扑排序
    else
        return true;  // 拓扑排序成功
}