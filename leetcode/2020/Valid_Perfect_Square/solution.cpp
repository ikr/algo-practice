using ll = long long;

struct Solution {
    bool isPerfectSquare(const int x) const {
        if (x == 1) return true;
        if (x == 2) return false;
        
        ll lo = 2;
        ll hi = x - 1;
        
        while (lo <= hi) {
            const ll mid = lo + (hi - lo) / 2;
            if (mid * mid == x) return true;
            
            if (mid * mid < x) lo = mid + 1;                
            else hi = mid - 1;
        }
        
        return false;
    }
};
