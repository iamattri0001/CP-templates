int sparseTable[500][500][10][10]; // adjust the size


class RMQ_2D {
private:
    vector<vector<int>> matrix;
    int n, m;
    void buildSparseTable() {
        int maxLogN = log2(n) + 1;
        int maxLogM = log2(m) + 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                sparseTable[i][j][0][0] = matrix[i][j];
            }
        }

        for (int k1 = 0; k1 < maxLogN; k1++) {
            for (int k2 = 0; k2 < maxLogM; k2++) {
                for (int i = 0; i + (1 << k1) <= n; i++) {
                    for (int j = 0; j + (1 << k2) <= m; j++) {
                        if (k1 == 0 && k2 == 0) {
                            continue;
                        }
                        if (k1 == 0) {
                            sparseTable[i][j][k1][k2] = max(sparseTable[i][j][k1][k2 - 1], sparseTable[i][j + (1 << (k2 - 1))][k1][k2 - 1]);
                        } else if (k2 == 0) {
                            sparseTable[i][j][k1][k2] = max(sparseTable[i][j][k1 - 1][k2], sparseTable[i + (1 << (k1 - 1))][j][k1 - 1][k2]);
                        } else {
                            int max1 = max(sparseTable[i][j][k1 - 1][k2 - 1], sparseTable[i + (1 << (k1 - 1))][j][k1 - 1][k2 - 1]);
                            int max2 = max(sparseTable[i][j + (1 << (k2 - 1))][k1 - 1][k2 - 1], sparseTable[i + (1 << (k1 - 1))][j + (1 << (k2 - 1))][k1 - 1][k2 - 1]);
                            sparseTable[i][j][k1][k2] = max(max1, max2);
                        }
                    }
                }
            }
        }
    }
public:
    RMQ_2D(const vector<vector<int>>& mat) : matrix(mat), n(mat.size()), m(mat[0].size()) {
        buildSparseTable();
    }

    int query(int x1, int y1, int x2, int y2) {
        if (x1 > x2 || y1 > y2) return INT_MIN;
        int k1 = log2(x2 - x1 + 1);
        int k2 = log2(y2 - y1 + 1);

        int max1 = max(sparseTable[x1][y1][k1][k2], sparseTable[x2 - (1 << k1) + 1][y1][k1][k2]);
        int max2 = max(sparseTable[x1][y2 - (1 << k2) + 1][k1][k2], sparseTable[x2 - (1 << k1) + 1][y2 - (1 << k2) + 1][k1][k2]);

        return max(max1, max2);
    }
};
