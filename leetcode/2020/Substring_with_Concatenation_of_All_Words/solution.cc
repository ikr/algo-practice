#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <optional>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (const T &x : xs) {
        os << x << ' ';
    }

    return os;
}

template <typename T> ostream &operator<<(ostream &os, const optional<T> &o) {
    if (o)
        os << *o;
    else
        os << '-';

    return os;
}

class Solution {
  public:
    vector<int> findSubstring(const string &hst, const vector<string> &words) {
        auto degen_result = degenerate_case_find(hst, words);
        if (degen_result)
            return *degen_result;

        vector<int> result;
        auto w_hash = total_hash(words);
        auto sz = words.begin()->size();
        auto cnt = words.size();
        const auto w_count_proto = initialize_w_count_map(words);

        for (int j = 0; j != sz && j + cnt * sz <= hst.size(); ++j) {
            auto rmatch_indices = rolling_match(hst, j, words, w_hash);

            for (int i : rmatch_indices) {
                if (stamping_match(hst, i, sz, w_count_proto))
                    result.push_back(i);
            }
        }

        return result;
    }

  private:
    static optional<vector<int>>
    degenerate_case_find(const string &hst, const vector<string> &words) {
        if (!hst.size() || !words.size() ||
            hst.size() < words.size() * words.begin()->size())
            return vector<int>{};

        if (!words.begin()->size()) {
            vector<int> result(hst.size() + 1);
            iota(result.begin(), result.end(), 0);
            return result;
        }

        if (words.size() == 1 && words.begin()->size() == hst.size())
            return {*words.begin() == hst ? vector<int>{0} : vector<int>{}};

        return nullopt;
    }

    static hash<string> chunk_hash;

    static int total_hash(const vector<string> &words) {
        int result = 0;

        for (const string &w : words) {
            result += chunk_hash(w);
        }

        return result;
    }

    static int total_hash(const string &joined_words, const int wsize) {
        int result = 0;

        for (int i = 0; i != joined_words.size(); i += wsize)
            result += chunk_hash(joined_words.substr(i, wsize));

        return result;
    }

    static vector<int> rolling_match(const string &hst, int start,
                                     const vector<string> &words, int whash) {
        auto sz = words.begin()->size();
        auto cnt = words.size();
        int th = total_hash(hst.substr(start, cnt * sz), sz);
        vector<int> result{};

        for (;;) {
            if (th == whash)
                result.push_back(start);

            if (start + (cnt + 1) * sz > hst.size())
                break;

            th = th - chunk_hash(hst.substr(start, sz)) +
                 chunk_hash(hst.substr(start + cnt * sz, sz));

            start += sz;
        }

        return result;
    }

    static bool
    stamping_match(const string &hst, int i, int sz,
                   const unordered_map<string, int> &w_count_proto) {
        unordered_map<string, int> w_count{w_count_proto};

        while (w_count.size()) {
            const string sub = hst.substr(i, sz);
            if (!w_count.count(sub))
                return false;

            --w_count[sub];
            if (!w_count[sub])
                w_count.erase(sub);

            i += sz;
        }

        return !w_count.size();
    }

    static unordered_map<string, int>
    initialize_w_count_map(const vector<string> &words) {
        unordered_map<string, int> w_count;

        for (const string &w : words) {
            ++w_count[w];
        }

        return w_count;
    }
};

hash<string> Solution::chunk_hash{};

void testcase(const string &hst, const vector<string> &words) {
    cout << hst << endl << words << endl;
    cout << Solution().findSubstring(hst, words) << endl << endl;
}

int main() {
    vector<pair<string, vector<string>>> samples = {
        {"barfoothefoobarman", {"foo", "bar"}},
        {"wordgoodgoodgoodbestword", {"word", "good", "best", "word"}},
        {"wordgoodgoodgoodbestword", {"word", "good", "best", "good"}},
        {"aaaaaaaa", {"aa", "aa", "aa"}},
        {"barfoofoobarthefoobarman", {"bar", "foo", "the"}},
        {"aaaaaa", {"aaa", "aaa"}},
        {"bbabbbab", {"ab", "bb", "bc", "ac"}}};

    for (auto s : samples) {
        testcase(s.first, s.second);
    }

    return 0;
}
