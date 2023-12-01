class BIT{
    vector<long long> tree;
    int n;

    long long sum(int i) {
        long long ans = 0;
        for(; i > 0; i -= (i & (-i)))
            ans += tree[i];
        return ans;
    }

    void point_update(int i, long long val) {
        for(; i <= n; i += (i & (-i)))
            tree[i] += val;
    }

public:
    BIT(int n) {
        tree.resize(n+1);
        this->n = n;
    }

    void range_update(int l, int r, long long val) {
        point_update(l, val);
        point_update(r+1, -val);
    }

    long long point_query(int i) {
        return sum(i);
    }
};
