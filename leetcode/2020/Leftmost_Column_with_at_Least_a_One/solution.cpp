/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int x, int y);
 *     vector<int> dimensions();
 * };
 */

int leftmost_col_with_1(BinaryMatrix &rows, const int row) {
    int lo = 0;
    int hi = rows.dimensions()[1];
    
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        
        if (rows.get(row, mid) == 1) {
            hi = mid;    
        } else {
            lo = mid + 1;
        }
    }
    
    return lo;
}

struct Solution final {
    int leftMostColumnWithOne(BinaryMatrix &rows) const {
        const int H = rows.dimensions()[0];
        const int W = rows.dimensions()[1];
        
        int ans = INT_MAX;
        
        for (int row = 0; row != H; ++row) {
            if (rows.get(row, W - 1) != 1) continue;
            ans = min(ans, leftmost_col_with_1(rows, row));
        }
        
        return ans == INT_MAX ? -1 : ans;
    }
};
