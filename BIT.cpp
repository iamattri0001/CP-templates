class BIT{
    vector<long long> tree;
    int N;
    
    long long sum(int i){
        long long ans = 0;
        for(; i>0; i -= (i & (-i)))
            ans += tree[i];
        return ans;
    }

public:
    BIT(int n){
        N = n;
        tree.resize(n+1);
    }

    long long query(int l, int r){
        return sum(r) - sum(l-1);
    }

    void update(int i, long long x){
        for(; i <= N; i += (i & (-i)))
            tree[i] += x;
    }
};
