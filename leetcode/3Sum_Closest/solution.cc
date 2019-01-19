#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class BruteForceSolution {
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

class Solution {
  public:
    int threeSumClosest(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        int result = nums[0] + nums[1] + nums.back();

        for (int i = 0; i < nums.size() - 2; ++i) {
            int x = target - nums[i];
            int l = i + 1;
            int r = nums.size() - 1;

            while (l < r) {
                int twoSum = nums[l] + nums[r];

                if (twoSum == x) {
                    return target;
                } else {
                    int candidate = nums[i] + nums[l] + nums[r];
                    if (abs(candidate - target) < abs(result - target)) {
                        result = candidate;
                    }
                }

                if (twoSum < x) {
                    ++l;
                } else {
                    --r;
                }
            }
        }

        return result;
    }
};

int main() {
    BruteForceSolution bs;
    Solution s;
    vector<int> v{1, 3, 3, 4, 4, 5, 61, 79, 28, 8, 24, 22, 21, 34, 45, 88, 9};

    cout << bs.threeSumClosest(v, 1) << '\n';
    cout << s.threeSumClosest(v, 1) << '\n';

    return 0;
}
