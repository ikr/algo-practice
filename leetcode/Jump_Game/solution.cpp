class Solution {
public:
    bool canJump(const vector<int> &xs) {
        const int sz = xs.size();
        
        for (int i = 0, charge = 0; i < sz; ++i, --charge) {
            charge = max(charge, xs[i]);
            if (!charge && i != sz - 1) return false;
        }
        
        return true;
    }
};
