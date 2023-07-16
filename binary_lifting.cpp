int up[200005][20];
#define vi vector<int>

void build_lift(vi adj[], int u, int par){
    up[u][0] = par;
    for(int i=1; i<20; i++){
        if(up[u][i-1] != -1)
            up[u][i] = up[up[u][i-1]][i-1];
        else
            up[u][i] = -1;
    }

    for(int child: adj[u])
        build_lift(adj, child, u);
}

int getQuery(int node, int jump){
    if(node == -1 || jump == 0)
        return node;

    for(int i=19; i>=0; i--){
        if(jump >= (1<<i))
            return getQuery(up[node][i], jump - (1<<i));
    }
    return 0;
}
