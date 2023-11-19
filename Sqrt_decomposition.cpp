class SqrtArray {
    vector<long long> chunk, arr;
    int n, len;
public:
    SqrtArray(vector<int> &v) {
        n = v.size();
        arr.resize(n);
        for(int i = 0; i < n; i++)
            arr[i] = v[i];

        len = sqrt(n);
        if(len * len < n)
            len++;

        chunk.resize(len);

        for(int i = 0; i < n; i++)
            chunk[i / len] += arr[i]; 
    }

    long long query(int l, int r) {
        long long sum = 0;
        while(l <= r) {
            if(l % len == 0 && l + len <= r) {
                sum += chunk[l / len];
                l += len;
            } else {
                sum += arr[l];
                l++;
            }
        }
        return sum;
    }

    void update(int i, long long val) {
        chunk[i / len] += val;
        arr[i] += val;
    }

    long long get_value(int i) {
        return arr[i];
    }
};
