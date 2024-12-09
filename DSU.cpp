class DSU {
    vector<int> par, siz;

public:
    DSU(int n) : par(n), siz(n, 1) { iota(par.begin(), par.end(), 0); }

    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)
            return 0;

        if (siz[u] < siz[v])
            swap(u, v);

        siz[u] += siz[v];
        par[v] = u;
        return 1;
    }

    int find(int u) {
        if (par[u] == u)
            return u;

        return par[u] = find(par[u]);
    }
};
