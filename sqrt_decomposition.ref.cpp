struct Block {
    long long lazy = 0;
    unordered_map<int, int> f;

    int query(int x) const {
        auto it = f.find(x - lazy);
        return it == f.end() ? 0 : it->second;
    }
};

class SqrtDecom {
    vector<Block> blocks;
    vector<long long> ary;
    int len;
    int n;

    void push(int blockId) {
        auto &b = blocks[blockId];

        if (b.lazy == 0)
            return;

        int start = blockId * len;
        int end = min(n, start + len);

        b.f.clear();

        for (int i = start; i < end; i++) {
            ary[i] += b.lazy;
            b.f[ary[i]]++;
        }

        b.lazy = 0;
    }

public:
    SqrtDecom(const vector<int> &a) {
        n = (int)a.size();

        len = sqrt(n);
        if (len * len < n)
            len++;

        int numBlocks = (n + len - 1) / len;

        blocks.resize(numBlocks);
        ary.resize(n);

        for (int i = 0; i < n; i++) {
            ary[i] = a[i];
            blocks[i / len].f[ary[i]]++;
        }
    }

    int query(int l, int r, int val) {
        int ans = 0;

        while (l <= r) {
            if (l % len == 0 && l + len - 1 <= r) {
                ans += blocks[l / len].query(val);
                l += len;
            } else {
                ans += (ary[l] + blocks[l / len].lazy == val);
                l++;
            }
        }

        return ans;
    }

    void add(int l, int r, int x) {
        while (l <= r) {
            if (l % len == 0 && l + len - 1 <= r) {
                blocks[l / len].lazy += x;
                l += len;
            } else {
                int blockId = l / len;

                push(blockId);

                auto &b = blocks[blockId];

                b.f[ary[l]]--;
                if (b.f[ary[l]] == 0)
                    b.f.erase(ary[l]);

                ary[l] += x;

                b.f[ary[l]]++;

                l++;
            }
        }
    }
};
