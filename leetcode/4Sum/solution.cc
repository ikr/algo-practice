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

class BruteForceSolution {
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        set<vector<int>> result_set;

        for (auto i = 0; i < nums.size() - 3; ++i) {
            for (auto j = i + 1; j < nums.size() - 2; ++j) {
                for (auto k = j + 1; k < nums.size() - 1; ++k) {
                    for (auto l = k + 1; l < nums.size(); ++l) {
                        if (nums[i] + nums[j] + nums[k] + nums[l] == target) {
                            vector<int> v{nums[i], nums[j], nums[k], nums[l]};
                            sort(v.begin(), v.end());
                            result_set.insert(v);
                        }
                    }
                }
            }
        }

        return vectorize(result_set);
    }

  private:
    static vector<vector<int>> vectorize(const set<vector<int>> &source) {
        vector<vector<int>> result;
        copy(source.begin(), source.end(), back_inserter(result));
        return result;
    }
};

class Solution {
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        set<vector<int>> result_set;

        for (auto i = 0; i < nums.size() - 3; ++i) {
            for (auto j = i + 1; j < nums.size() - 2; ++j) {
                int l = j + 1;
                int r = nums.size() - 1;

                while (l < r) {
                    int candidate = nums[i] + nums[j] + nums[l] + nums[r];

                    if (candidate == target) {
                        result_set.insert(
                            vector<int>{nums[i], nums[j], nums[l], nums[r]});
                        break;
                    }

                    if (candidate < target) {
                        ++l;
                    } else {
                        --r;
                    }
                }
            }
        }

        return vectorize(result_set);
    }

  private:
    static vector<vector<int>> vectorize(const set<vector<int>> &source) {
        vector<vector<int>> result;
        copy(source.begin(), source.end(), back_inserter(result));
        return result;
    }
};

int main() {
    Solution s;
    vector<int> nums{1, 0, -1, 0, -2, 2};
    auto result = s.fourSum(nums, 0);

    for (auto quad : result) {
        for (auto x : quad) {
            cout << x << ' ';
        }

        cout << endl;
    }

    return 0;
}
