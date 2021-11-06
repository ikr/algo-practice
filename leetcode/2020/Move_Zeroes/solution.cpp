class Solution {
public:
    void moveZeroes(vector<int>& xs) {
        stable_partition(xs.begin(), xs.end(), [](const int x) { return !!x; });
    }
};
