// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

struct Solution final {
    int firstBadVersion(const int n) const {
        int lo = 1, hi = n, ans = INT_MAX;
        
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            
            if (isBadVersion(mid)) {
                ans = min(ans, mid);
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        
        return ans;
    }
};
