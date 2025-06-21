class WaveletTree {
    WaveletTree *left, *right;
    vector<int> prefix_count;
    int lo, hi;

public:
    WaveletTree() : left(nullptr), right(nullptr) {}

    ~WaveletTree() {
        delete left;
        delete right;
    }

    // build WT for values in range [low_value...high_value] and a[l...r-1]
    WaveletTree(vector<int>& a, int low_value, int high_value, int l, int r)
        : lo(low_value), hi(high_value), left(nullptr), right(nullptr) {
        if (lo == hi || l >= r) return;

        int mid = (lo + hi) >> 1;
        auto fx = [mid](int x) { return x <= mid; };

        prefix_count.reserve(r - l + 1);
        prefix_count.push_back(0);
        for (int i = l; i < r; ++i) {
            prefix_count.push_back(prefix_count.back() + fx(a[i]));
        }

        auto it = stable_partition(a.begin() + l, a.begin() + r, fx);
        int pivot = it - a.begin();

        left = new WaveletTree(a, lo, mid, l, pivot);
        right = new WaveletTree(a, mid + 1, hi, pivot, r);
    }

    // count of values in a[l..r] that are in value range [x..y], l and r are 0-based inclusive
    int query(int l, int r, int x, int y) {
        if (r < l || y < lo || x > hi) return 0; // no overlap
        if (x <= lo && hi <= y) return r - l + 1; // complete overlap

        int left_l = prefix_count[l]; // prefix array has 1 based indexing
        int left_r = prefix_count[r + 1];

        int in_left = left ? left->query(left_l, left_r - 1, x, y) : 0;
        int in_right = right ? right->query(l - left_l, r - left_r, x, y) : 0;

        return in_left + in_right;
    }
};
