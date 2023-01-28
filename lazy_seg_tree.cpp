#include <bits/stdc++.h>
using namespace std;

#define leftChild(i) (2 * i + 1)
#define rightChild(i) (2 * i + 2)
#define midPt(low, high) (low + (high - low) / 2)
#define INF 1e9
#define MIN_INF -1e9

int lazy[int(1e5)] = {0}; // lazy is declared global, make it zero after every test case

void buildTree(int arr[], int start, int end, int *tree, int i = 0)
{
    if (start == end)
    {
        tree[i] = arr[start];
        return;
    }

    int mid = midPt(start, end);
    buildTree(arr, start, mid, tree, leftChild(i));
    buildTree(arr, mid + 1, end, tree, rightChild(i));

    tree[i] = max(tree[leftChild(i)], tree[rightChild(i)]);
}

int queryLazy(int q_start, int q_end, int *tree, int low, int high, int i = 0)
{
    if (lazy[i] != 0)
    {
        tree[i] += lazy[i];
        lazy[leftChild(i)] += lazy[i];
        lazy[rightChild(i)] += lazy[i];
        lazy[i] = 0;
    }

    if (q_start > high || q_end < low)
        return MIN_INF;

    if (low >= q_start && high <= q_end)
        return tree[i];
    int mid = midPt(low, high);
    int left = queryLazy(q_start, q_end, tree, low, mid, leftChild(i));
    int right = queryLazy(q_start, q_end, tree, mid + 1, high, rightChild(i));

    return max(left, right);
}

void updateLazy(int q_start, int q_end, int change, int *tree, int low, int high, int i = 0)
{
    // for single point update, pass (q_start = q_end = the index of point to be updated)
    if (lazy[i] != 0)
    {
        tree[i] += lazy[i];
        lazy[leftChild(i)] += lazy[i];
        lazy[rightChild(i)] += lazy[i];
        lazy[i] = 0;
    }

    if (q_end < low || q_start > high)
        return;

    if (low >= q_start && high <= q_end)
    {
        tree[i] += change;
        lazy[leftChild(i)] += change;
        lazy[rightChild(i)] += change;
        return;
    }

    int mid = midPt(low, high);
    updateLazy(q_start, q_end, change, tree, low, mid, leftChild(i));
    updateLazy(q_start, q_end, change, tree, mid + 1, high, rightChild(i));

    tree[i] = max(tree[leftChild(i)], tree[rightChild(i)]);
    return;
}

int main()
{
    int arr[] = {2, 3, 5, -9, 18, 4, 27, 8};
    int n = sizeof(arr) / sizeof(int);
    int t_size = 4 * n;
    int *tree = new int[t_size];
    buildTree(arr, 0, n - 1, tree);

    // for(int i=0; i<t_size; i++)
    //     cout<<tree[i]<<" ";

    updateLazy(4, 7, 10, tree, 0, n - 1);
    updateLazy(2, 4, 12, tree, 0, n - 1);
    cout << queryLazy(0, 1, tree, 0, n - 1) << endl;
}
