#include <cmath>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

class Solution {
  public:
    int threeSumClosest(vector<int> &nums, int target) {
        int result = nums[0] + nums[1] + nums[2];

        for (int i = 1; i < nums.size() - 2; ++i) {
            for (int j = i + 1; j < nums.size() - 1; ++j) {
                for (int k = j + 1; k < nums.size(); ++k) {
                    int candidate = nums[i] + nums[j] + nums[k];
                    if (abs(candidate - target) < abs(result - target)) {
                        result = candidate;
                    }
                }
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    vector<int> v{-1, 2, 1, -4};

    cout << s.threeSumClosest(v, 1) << '\n';

    return 0;
}
