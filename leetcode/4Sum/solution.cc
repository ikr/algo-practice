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

class VectorHash {
  public:
    int operator()(const vector<int> &v) const {
        if (v.empty()) {
            return 0;
        }

        vector<int>::const_iterator it = v.begin();
        int result = *it;
        ++it;

        while (it != v.end()) {
            result = 31 * result + *it;
            ++it;
        }

        return result;
    }
};

using QuadsSet = unordered_set<vector<int>, VectorHash>;

class BruteForceSolution {
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        QuadsSet result_set;

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
    static vector<vector<int>> vectorize(const QuadsSet &source) {
        vector<vector<int>> result;
        copy(source.begin(), source.end(), back_inserter(result));
        return result;
    }
};

class NCubeSolution {
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        if (nums.size() < 4) {
            return vector<vector<int>>();
        }

        sort(nums.begin(), nums.end());
        QuadsSet result_set;

        for (auto i = 0; i < nums.size() - 3; ++i) {
            for (auto j = i + 1; j < nums.size() - 2; ++j) {
                int l = j + 1;
                int r = nums.size() - 1;

                while (l < r) {
                    int candidate = nums[i] + nums[j] + nums[l] + nums[r];

                    if (candidate == target) {
                        result_set.insert(
                            vector<int>{nums[i], nums[j], nums[l], nums[r]});
                        ++l;
                    } else if (candidate < target) {
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
    static vector<vector<int>> vectorize(const QuadsSet &source) {
        vector<vector<int>> result;
        copy(source.begin(), source.end(), back_inserter(result));
        return result;
    }
};

struct IndexPair {
    int sum_of_elements;
    int i;
    int j;

    IndexPair(int sum_of_elements_, int i_, int j_)
        : sum_of_elements(sum_of_elements_), i(i_), j(j_) {}

    bool operator<(const IndexPair &other) const {
        return sum_of_elements < other.sum_of_elements;
    }
};

class NSquareLogNSolution {
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        if (nums.size() < 4) {
            return vector<vector<int>>();
        }

        vector<IndexPair> index_pairs;

        for (auto i = 0; i < nums.size() - 1; ++i) {
            for (auto j = i + 1; j < nums.size(); ++j) {
                index_pairs.push_back(IndexPair(nums[i] + nums[j], i, j));
            }
        }

        sort(index_pairs.begin(), index_pairs.end());

        QuadsSet result_set;
        auto l = 0;
        auto r = index_pairs.size() - 1;

        while (l < r) {
            auto lp = index_pairs[l];
            auto rp = index_pairs[r];

            if (lp.sum_of_elements + rp.sum_of_elements == target) {
                unordered_set<int> candidate{lp.i, lp.j, rp.i, rp.j};
                if (candidate.size() == 4) {
                    vector<int> v{nums[lp.i], nums[lp.j], nums[rp.i],
                                  nums[rp.j]};
                    sort(v.begin(), v.end());
                    result_set.insert(v);
                }
                ++l;
            } else if (lp.sum_of_elements + rp.sum_of_elements < target) {
                ++l;
            } else {
                --r;
            }
        }

        return vectorize(result_set);
    }

  private:
    static vector<vector<int>> vectorize(const QuadsSet &source) {
        vector<vector<int>> result;
        copy(source.begin(), source.end(), back_inserter(result));
        return result;
    }
};

int main() {
    NSquareLogNSolution s;
    vector<int> nums{1, 0, -1, 0, -2, 2};

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
