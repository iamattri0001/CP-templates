#include <bits/stdc++.h>
using namespace std;

#define leftChild(i) (2 * i + 1)
#define rightChild(i) (2 * i + 2)
#define midPt(low, high) (low + (high - low) / 2)
#define INF 1e9
#define MIN_INF -1e9


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

int queryTree(int q_start, int q_end, int *tree, int low, int high, int i = 0)
{
    if (q_start <= low && q_end >= high)
        return tree[i];

    if (q_start > high || q_end < low)
        return MIN_INF;

    int mid = midPt(low, high);
    int left = queryTree(q_start, q_end, tree, low, mid, leftChild(i));
    int right = queryTree(q_start, q_end, tree, mid + 1, high, rightChild(i));

    return max(left, right);
}



void updateNode(int idx, int change, int *tree, int low, int high, int i = 0)
{
    if (idx < low || idx > high)
        return;

    if (low == high)
    {
        tree[i] += change;
        return;
    }

    int mid = midPt(low, high);

    if (idx <= mid)
        updateNode(idx, change, tree, low, mid, leftChild(i));
    else
        updateNode(idx, change, tree, mid + 1, high, rightChild(i));

    tree[i] = max(tree[leftChild(i)], tree[rightChild(i)]);
}

void updateRange(int q_start, int q_end, int change, int *tree, int low, int high, int i = 0)
{
    if (q_start > high || q_end < low)
        return;

    if (low == high)
    {
        tree[i] += change;
        return;
    }

    int mid = midPt(low, high);
    updateRange(q_start, q_end, change, tree, low, mid, leftChild(i));
    updateRange(q_start, q_end, change, tree, mid + 1, high, rightChild(i));

    tree[i] = max(tree[leftChild(i)], tree[rightChild(i)]);
}

int main(){
  int arr[] = {1,2,3,4};
  int n = sizeof(arr)/sizeof(int);
  int *tree = new int[4*n+1];
  buildTree(arr, 0, n-1, tree);
}
