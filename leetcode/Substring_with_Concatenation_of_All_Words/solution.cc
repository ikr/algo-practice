#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> findSubstring(const string &hst, const vector<string> &words) {
        auto degenerate_case_res = degen_case(hst, words);
        if (degenerate_case_res.first)
            return vector<int>{degenerate_case_res.second};

        vector<int> result;
        auto word_hashes = hash_all(words);
        auto words_set = make_set(words);
        auto sz = words.begin()->size();
        auto cnt = words.size();
        auto bound = hst.size() - cnt * sz + 1;

        for (int i = 0, h0 = 0; i != bound; ++i) {
            const int h = (i == 0) ? hash_one(hst.substr(0, sz))
                                   : rolling_hash(hst, h0, i, sz);

            if (word_hashes.count(h) && words_set.count(hst.substr(i, sz))) {
                if (stamping_match(hst, i, words))
                    result.push_back(i);
            }

            h0 = h;
        }

        return result;
    }

  private:
    static pair<bool, int> degen_case(const string &hst,
                                      const vector<string> &words) {
        if (!words.size())
            return make_pair(true, 0);

        if (!words.begin()->size())
            return make_pair(true, 0);

        if (hst.size() < words.size() * words.begin()->size())
            return make_pair(true, -1);

        if (words.size() == 1 && words.begin()->size() == hst.size())
            return make_pair(true, *words.begin() == hst ? 0 : -1);

        return make_pair(false, -1);
    }

    static unordered_set<int> hash_all(const vector<string> &words) {
        // TODO
        return unordered_set<int>{};
    }

    static unordered_set<string> make_set(const vector<string> &words) {
        // TODO
        return unordered_set<string>{};
    }

    static int hash_one(const string &s) {
        // TODO
        return 0;
    }

    static int rolling_hash(const string &s, const int prev_hash,
                            const int start_index, const int sz) {
        // TODO
        return 0;
    }

    static bool stamping_match(const string &hst, int index,
                               const vector<string> &words) {
        // TODO
        return false;
    }
};

int main() {
    Solution s;

    cout << endl;

    return 0;
}
