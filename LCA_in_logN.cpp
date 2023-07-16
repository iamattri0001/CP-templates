// call binary_lift() before queries
const int LOG = 20;
const int N = 2e5;
int up[N][LOG];
vector<int> lvl; //resize it


void binary_lift(vector<int> adj[], int u, int par, int l){
    up[u][0] = par;
    lvl[u] = l;
    for(int i=1; i<LOG; i++){
        if(up[u][i-1] != -1)
            up[u][i] = up[up[u][i-1]][i-1];
        else
            up[u][i] = -1;
    }

    for(int v: adj[u])
        if(v != par)
            binary_lift(adj, v, u, l+1);
}

int lift_node(int node, int jump){
    for(int i=LOG-1; i>=0; i--){
        if(jump == 0 || node == -1)
            break;
        if(jump >= (1<<i)){
            jump -= (1<<i);
            node = up[node][i];
        }
    }
    return node;
}

int get_lca(int u, int v){
    if(lvl[u] < lvl[v])
        swap(u, v);
    u = lift_node(u, lvl[u] - lvl[v]);
    if(u == v)
        return u;

    for(int i = LOG-1; i>=0; i--)
        if(up[u][i] != up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    return lift_node(u, 1);
}
