class Solution {
public:
    int minMoves(const vector<int> &xs) const {
        const int lo = *min_element(xs.cbegin(), xs.cend());
        
        return accumulate(xs.cbegin(), xs.cend(), 0, [lo](const int agg, const int x) { 
            return agg + x - lo; 
        });
    }
};
