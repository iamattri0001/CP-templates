template<typename Node, typename Update>
struct SegTree {
    vector<Node> tree;
    vector<long long> arr;
    int n, s;
    SegTree(int N, vector<long long> &a) {
        arr = a;
        n = N;

        s = 1;
        while (s < 2 * n) {
            s <<= 1;
        }

        tree.resize(s);
        fill(tree.begin(), tree.end(), Node());
        build(1, 0, n - 1);
    }

    void build(int index, int low, int high) {
        if (low == high) {
            tree[index] = Node(arr[low]);
            return;
        }

        int mid = low + (high - low) / 2;
        build(2 * index, low, mid);
        build(2 * index + 1, mid + 1, high);

        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }

    void update(int upd_index, int index, int low, int high, Update &u) {
        if (low == high) {
            u.apply(tree[index]);
            return;
        }

        int mid = low + (high - low) / 2;
        if (mid >= upd_index)
            update(upd_index, 2 * index, low, mid, u);
        else
            update(upd_index, 2 * index + 1, mid + 1, high, u);

        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }

    Node query(int q_low, int q_high, int index, int low, int high) {
        if (q_low > high || q_high < low)
            return Node();

        if (q_low <= low && q_high >= high)
            return tree[index];

        int mid = low + (high - low) / 2;
        Node l = query(q_low, q_high, 2 * index, low, mid);
        Node r = query(q_low, q_high, 2 * index + 1, mid + 1, high);

        Node ans;
        ans.merge(l, r);
        return ans;
    }

    void make_update(int index, long long value) {
        Update new_update = Update(value);
        update(index, 1, 0, n - 1, new_update);
    }

    Node make_query(int low, int high) {
        return query(low, high, 1, 0, n - 1);
    }
};


struct SegNode {
    long long value;
    SegNode() {
        value = 0;
    }
    SegNode(long long x) {
        value = x;
    }
    void merge(SegNode &n1, SegNode &n2) {
        value = n1.value + n2.value;
    }
};

struct SegUpdate {
    long long value;
    SegUpdate(long long x) {
        value = x;
    }
    void apply(SegNode &n) {
        n.value = value;
    }
};


// auto s = SegTree<SegNode, SegUpdate>(n, arr);
