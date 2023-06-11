// build: (input array, 0, n-1)
// query: (0, n-1, query start, query end)
// update: (0, n-1, position, new value)

//point updates only

class SegTree{
    vector<ll> tree;
public:
    SegTree(int n = 1){
        tree.resize(4*n);
    }
    
    void build(vi &arr, int low, int high, int idx = 0){
        if(low == high){
            tree[idx] = arr[low];
            return;
        }

        int mid = (low+high)/2;

        build(arr, low, mid,  2*idx+1);
        build(arr, mid+1, high, 2*idx+2);

        tree[idx] = tree[2*idx+1] + tree[2*idx+2];
    }

    ll query(int low, int high, int ql, int qh, int idx=0){
        if(low > qh || high < ql)
            return 0;

        if(ql <= low && qh >= high)
            return tree[idx];

        int mid = (low+high)/2;
        ll left = query(low, mid, ql, qh, 2*idx+1);
        ll right = query(mid+1, high, ql, qh, 2*idx+2);

        return left + right;
    }

    void update(int low, int high, int pos, int val, int idx = 0){
        if(pos < low || pos > high)
            return;
        if(low == high){
            tree[idx] = val;
            return;
        }

        int mid = (low+high)/2;

        if(pos <= mid)
            update(low, mid, pos, val, 2*idx+1);
        else
            update(mid+1, high, pos, val, 2*idx+2);

        tree[idx] = tree[2*idx+1] + tree[2*idx+2];
    }
};
