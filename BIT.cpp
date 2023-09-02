// 1. BIT t(size of the array);
// 2. t.build(the input array as vector)
// 3. use 1-based indexing for t.sum(from index, to index) and t.add(index, value to be added);

class BIT{
    vector<long long> tree;
    int N;
    
    long long sum(int i){
        long long ans = 0;
        for(; i>0; i -= (i & (-i)))
            // i & (-i) gives highest set-bit in 'i'
            ans += tree[i];
        return ans;
    }

public:
    BIT(int n){
        N = n;
        tree.resize(n+1);
    }

    long long sum(int l, int r){
        return sum(r) - sum(l-1);
    }

    void add(int i, long long x){
        for(; i <= N; i += (i & (-i)))
            tree[i] += x;
    }

    void build(vector<int> &v) {
        for(int i=0; i<N; i++)
            add(i+1, v[i]);
    }
};
