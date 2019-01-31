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

using KeyedPairs = unordered_multimap<int, pair<int, int>>;

class NSquareLogNSolution {
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        QuadsSet result_set;
        KeyedPairs pairsBySum = all_pairs_by_their_sum(nums);
        unordered_set<int> keys = unique_keys(pairsBySum);

        for (auto i = keys.begin(); i != keys.end(); ++i) {
            if (keys.count(target - *i) == 1) {
                QuadsSet qs = combine_quads(
                    *i, pairsBySum.find(*i), target - *i,
                    pairsBySum.find(target - *i), pairsBySum.end());

                result_set.insert(qs.begin(), qs.end());
            }
        }

        return vectorize(result_set);
    }

  private:
    static unordered_set<int> unique_keys(const KeyedPairs &m) {
        unordered_set<int> result;

        for (auto i = m.begin(); i != m.end(); ++i) {
            result.insert(i->first);
        }

        return result;
    }

    static QuadsSet combine_quads(int pair_one_sum,
                                  KeyedPairs::const_iterator pair_one_it,
                                  int pair_two_sum,
                                  KeyedPairs::const_iterator pair_two_it,
                                  KeyedPairs::const_iterator end) {
        QuadsSet result;

        if (pair_one_it == pair_two_it) {
            for (auto i = pair_one_it; i != end && i->first == pair_one_sum;
                 ++i) {
                for (auto j = i; ++j != end && j->first == pair_two_sum;) {
                    result.insert(quad(i, j));
                }
            }
        } else {
            for (auto i = pair_one_it; i != end && i->first == pair_one_sum;
                 ++i) {
                for (auto j = pair_two_it; j != end && j->first == pair_two_sum;
                     ++j) {
                    result.insert(quad(i, j));
                }
            }
        }

        return result;
    }

    static vector<int> quad(KeyedPairs::const_iterator i,
                            KeyedPairs::const_iterator j) {
        vector<int> v{i->second.first, i->second.second, j->second.first,
                      j->second.second};

        sort(v.begin(), v.end());
        return v;
    }

    static KeyedPairs all_pairs_by_their_sum(const vector<int> &xs) {
        KeyedPairs result;

        for (auto i = 0; i < xs.size() - 1; ++i) {
            for (auto j = i; j < xs.size(); ++j) {
                result.insert({xs[i] + xs[j], {xs[i], xs[j]}});
            }
        }

        return result;
    }

    static vector<vector<int>> vectorize(const QuadsSet &source) {
        vector<vector<int>> result;
        copy(source.begin(), source.end(), back_inserter(result));
        return result;
    }
};

int main() {
    NSquareLogNSolution s;
    vector<int> nums{-3, -2, -1, 0, 0, 1, 2, 3};

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
