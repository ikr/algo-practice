#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        if (nums.size() < 4) {
            return vector<vector<int>>();
        }

        sort(nums.begin(), nums.end());
        vector<vector<int>> result;

        for (auto i = 0; i < nums.size() - 3; ++i) {
            for (auto j = i + 1; j < nums.size() - 2; ++j) {
                int l = j + 1;
                int r = nums.size() - 1;

                while (l < r) {
                    int candidate = nums[i] + nums[j] + nums[l] + nums[r];

                    if (candidate == target) {
                        vector<int> v{nums[i], nums[j], nums[l], nums[r]};
                        result.push_back(v);
                        ++l;
                    } else if (candidate < target) {
                        ++l;
                    } else {
                        --r;
                    }
                }
            }
        }

        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());

        return result;
    }
};

int main() {
    Solution s;
    // vector<int> nums{1, 0, -1, 0, -2, 2};
    vector<int> nums{-3, -1, 0, 2, 4, 5};
    // vector<int> nums{-4, -3, -2, -1, 0, 0, 1, 2, 3, 4};

    for (auto x : nums) {
        cout << x << ' ';
    }
    cout << endl;

    auto result = s.fourSum(nums, 0);

    for (auto quad : result) {
        for (auto x : quad) {
            cout << x << ' ';
        }

        cout << endl;
    }

    return 0;
}
