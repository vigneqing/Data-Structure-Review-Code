/* ═══════════════════════════════════════════════════════════════════
 * 图的应用算法（Graph Applications）
 * ─────────────────────────────────────────────────────────────────
 * 主要内容：最小生成树 / 最短路径 / 图遍历相关算法
 * 适用范围：无向带权图、非负权图、全源最短路等问题
 * ═══════════════════════════════════════════════════════════════════ */

/* ─────────────────────────────────────────
 * 一、Prim 算法
 * 适用：无向带权图
 * 思想：每次从当前生成树中选择到未加入顶点的最小权值边，
 *       将对应顶点加入最小生成树中，直到所有顶点都被覆盖
 * ───────────────────────────────────────── */

void Prim(MGraph G, int v0) {
   int lowCost[MaxVertexNum], closest[MaxVertexNum];
   bool visited[MaxVertexNum];
   for (int i = 0; i < G.vexnum; ++i) {
       lowCost[i] = G.Edge[v0][i];
       closest[i] = v0;
       visited[i] = false;
   }
   visited[v0] = true;
   lowCost[v0] = 0;
   for (int i = 1; i < G.vexnum; ++i) {
       int min = INFINITY, k = -1;
       for (int j = 0; j < G.vexnum; ++j) {
           if (!visited[j] && lowCost[j] < min) {
               min = lowCost[j];
               k = j;
           }
       }
       if (k == -1) break;
       visited[k] = true;
       for (int j = 0; j < G.vexnum; ++j) {
           if (!visited[j] && G.Edge[k][j] < lowCost[j]) {
               lowCost[j] = G.Edge[k][j];
               closest[j] = k;
           }
       }
   }
}

/* ─────────────────────────────────────────
 * 二、Kruskal 算法
 * 适用：无向带权图
 * 思想：按边权从小到大依次选择，若两端点不在同一集合中，
 *       则将该边加入最小生成树，最终形成最小生成树
 * ───────────────────────────────────────── */

typedef struct {
   int u, v;
   int w;
} Edge;

int parent[MaxVertexNum];
void InitUnionSet(int n) {
   for (int i = 0; i < n; ++i) parent[i] = i;
}
int Find(int x) {
   if (parent[x] == x) return x;
   return parent[x] = Find(parent[x]);
}
void Union(int x, int y) {
   int fx = Find(x), fy = Find(y);
   if (fx != fy) parent[fx] = fy;
}

void Kruskal(MGraph G) {
   Edge edges[MaxVertexNum * MaxVertexNum];
   int edgeNum = 0;
   for (int i = 0; i < G.vexnum; ++i) {
       for (int j = i + 1; j < G.vexnum; ++j) {
           if (G.Edge[i][j] != INFINITY) {
               edges[edgeNum].u = i;
               edges[edgeNum].v = j;
               edges[edgeNum].w = G.Edge[i][j];
               ++edgeNum;
           }
       }
   }
   // sort(edges, edges + edgeNum, cmp);
   InitUnionSet(G.vexnum);
   for (int i = 0; i < edgeNum; ++i) {
       if (Find(edges[i].u) != Find(edges[i].v)) {
           Union(edges[i].u, edges[i].v);
           // 选择该边
       }
   }
}

/* ─────────────────────────────────────────
 * 三、BFS 算法
 * 作用：求顶点 u 到其余所有顶点的最短路径（适用于无权图）
 * 思想：利用队列按层更新，越早到达的顶点路径更短
 * ───────────────────────────────────────── */
void BFS_MIN_Distance(Graph G, int u) {
    //d[i]表示从u到i的最短距离
    for(i=0;i<G.vexnum;++i){
        d[i]=INFINITY;//初始化路径长度
        path[i]=-1;//从哪个顶点过来
    }
    d[u]=0;//初始化起点到起点的距离
    visited[u]=true;//起点访问
    Enqueue(Q,u);//起点入队
    while(!isEmpty(Q)) {
        Dequeue(Q, u);
        for (w = FirstNeighbor(G, u), w >= 0; w = NextNeighbor(G, u, w))
            if (!visited[w]) {
                d[w] = d[u] + 1;
                path[w] = u;
                visited[w] = true;
                Enqueue(Q, w);
            }
    }
}

/* ─────────────────────────────────────────
 * 四、Dijkstra 算法
 * 适用：非负权图
 * 思想：每次从未确定最短路的顶点中选出当前距离最小的点，
 *       逐步更新其他顶点的最短距离，直到求出源点到所有点的最短路
 * ───────────────────────────────────────── */

void Dijkstra(MGraph G, int v0) {
   int dist[MaxVertexNum], path[MaxVertexNum];
   bool visited[MaxVertexNum];
   for (int i = 0; i < G.vexnum; ++i) {
       dist[i] = G.Edge[v0][i];
       path[i] = (G.Edge[v0][i] != INFINITY) ? v0 : -1;
       visited[i] = false;
   }
   dist[v0] = 0; visited[v0] = true;
   for (int i = 1; i < G.vexnum; ++i) {
       int min = INFINITY, u = -1;
       for (int j = 0; j < G.vexnum; ++j) {
           if (!visited[j] && dist[j] < min) {
               min = dist[j];
               u = j;
           }
       }
       if (u == -1) break;
       visited[u] = true;
       for (int j = 0; j < G.vexnum; ++j) {
           if (!visited[j] && G.Edge[u][j] != INFINITY &&
               dist[u] + G.Edge[u][j] < dist[j]) {
               dist[j] = dist[u] + G.Edge[u][j];
               path[j] = u;
           }
       }
   }
}

/* ─────────────────────────────────────────
 * 五、Floyd 算法
 * 适用：全源最短路径问题
 * 思想：通过中间顶点逐步松弛任意两点之间的最短距离，
 *       适合求任意顶点对之间的最短路
 * ───────────────────────────────────────── */

void Floyd(MGraph G) {
   int dist[MaxVertexNum][MaxVertexNum];
   int path[MaxVertexNum][MaxVertexNum];
   for (int i = 0; i < G.vexnum; ++i) {
       for (int j = 0; j < G.vexnum; ++j) {
           dist[i][j] = G.Edge[i][j];
           path[i][j] = -1;
           if (i != j && G.Edge[i][j] != INFINITY)
               path[i][j] = i;
       }
   }
   for (int k = 0; k < G.vexnum; ++k) {
       for (int i = 0; i < G.vexnum; ++i) {
           for (int j = 0; j < G.vexnum; ++j) {
               if (dist[i][k] != INFINITY && dist[k][j] != INFINITY &&
                   dist[i][k] + dist[k][j] < dist[i][j]) {
                   dist[i][j] = dist[i][k] + dist[k][j];
                   path[i][j] = path[k][j];
               }
           }
       }
   }
}

/*
 * 补充说明：
 * Prim / Kruskal：用于求最小生成树，目标是在保证连通的前提下使总权值最小。
 * BFS：适用于无权图的单源最短路问题，通常用于求最少步数或最短路径。
 * Dijkstra：适用于非负权图的单源最短路问题，能够高效求出最短距离。
 * Floyd：适用于全源最短路径问题，可直接求任意两点之间的最短距离。
 */
