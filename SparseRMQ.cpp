class SparseRMQ {
    vector<vector<int>> st;
    int K;
    vector<int> lg;

    static int log2_floor(unsigned long long i) { // not in use
        return i ?  : -1;
    }

    inline int f(int x, int y) {
        return max(x, y); // change here for max/min
    }

public:
    SparseRMQ(vector<int> &nums) {
        int n = nums.size();
        K = log2(n);

        // pre-compute all log2 for O(1) query
        lg.resize(n + 1);
        lg[0] = -1;
        for(int i = 1; i <= n; i++) {
            lg[i] = __builtin_clzll(1) - __builtin_clzll(i);
        }

        
        st.resize(K + 1, vector<int>(n));
        for(int i = 0; i < n; i++) {
            st[0][i] = nums[i];
        }

        for(int i = 1; i <= K; i++) {
            for(int j = 0; j + (1 << i) <= n; j++) {
                st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int RMQ(int a, int b) { // 0 based indexing
        int i = lg[b - a + 1];
        return f(st[i][a], st[i][b - (1 << i) + 1]);
    }
};
