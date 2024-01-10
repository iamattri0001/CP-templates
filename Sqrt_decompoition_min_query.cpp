class SqrtArray {
    vector<int> array, chunk;
    int len, n;
public: 
    SqrtArray(int n) : array(n, 1e9) {
        len = sqrt(n);
        if(len * len != n)
            len++;
        chunk.resize(len, 1e9);
        this->n = n;
    }

    int get_min(int l, int r) {
        int ans = 1e9;
        for(int i = l; i <= r;) {
            if(i % len == 0 && i + len <= r) {
                ans = min(ans, chunk[i / len]);
                i += len;
            } else {
                ans = min(ans, array[i]);
                i++;
            }
        }

        return ans;
    }

    void update(int idx, int value) {
        array[idx] = value;
        int chunk_no = idx / len;
        int start = chunk_no * len;
        for(int i = start; i < start + len && i < n; i++) {
            chunk[i / len] = min(chunk[i / len], array[i]);
        }
    }
};
