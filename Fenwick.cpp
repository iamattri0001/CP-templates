// 0 based indexing
class Fenwick {
    vector<long long> tree;
    int n;
public:
    Fenwick(vector<int> &a) {
        n = a.size();
        tree.resize(n + 1);
        build(a);
    }

    Fenwick(int N) {
        n = N;
        tree.resize(n + 1);
    }

    void build(vector<int> &a) {
        for (int i = 0; i < n; i++)
            update(i, a[i]);
    }

    void update(int idx, long long val) {
        for (int i = idx + 1; i <= n; i += i & -i)
            tree[i] += val;
    }

    long long sum(int upto) {
        long long ans = 0;
        for (int i = upto + 1; i > 0; i -= i & -i)
            ans += tree[i];

        return ans;
    }

    long long query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};
