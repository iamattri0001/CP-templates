// Range min/max queries in O(1) with O(nlogn) pre-processing

class SparseRMQ {
    vector<vector<int>> st;
    int K;

    int log2_floor(unsigned long long i) {
        return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
    }

    inline int f(int x, int y) {
        return min(x, y); // change here for max/min
    }

public:
    SparseRMQ(vector<int> &nums) {
        int n = nums.size();
        K = log2(n);

        st.resize(K + 1, vector<int>(n));
        for(int i = 0; i < n; i++)
            st[0][i] = nums[i];

        for(int i = 1; i <= K; i++)
            for(int j = 0; j + (1 << i) <= n; j++)
                st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }

    int RMQ(int a, int b) { // zero based indexing
        int i = log2_floor(b - a + 1);
        return f(st[i][a], st[i][b - (1 << i) + 1]);
    }
};
