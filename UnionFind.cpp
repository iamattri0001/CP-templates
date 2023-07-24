class DSU{
    int *size, *par, N, groups;
    public:
    DSU(int n){
        par = new int[n];
        size = new int[n];
        N = n;
        groups = n-1;
        for(int i=1; i<n; i++){
            par[i] = i;
            size[i] = 1;
        }
    }

    int getPar(int u){
        if(par[u] == u)
            return u;
        return par[u] = getPar(par[u]);
    }

    int getSize(int u){
        return size[getPar(u)];
    }

    void unionBySize(int u, int v){
        int pu = getPar(u);
        int pv = getPar(v);
        if(pu == pv)
            return;

        if(size[pu] > size[pv]){
            size[pu] += size[pv];
            par[pv] = pu;
        }
        else{
            size[pv] += size[pu];
            par[pu] = pv;
        }
        groups--;
    }

    int isUnited(){
        return groups == 1;   
    }
};
