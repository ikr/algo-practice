#include <algorithm>
#include <cassert>
#include <cmath>
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

template <typename T>
ostream &operator<<(ostream &os, const unordered_set<T> &xs) {
    for (const T &x : xs) {
        os << x << ' ';
    }

    return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const unordered_map<K, V> &m) {
    for (auto i = m.begin(); i != m.end(); ++i) {
        os << i->first << ":" << i->second << " ";
    }

    return os;
}

class Solution {
  public:
    vector<int> findSubstring(const string &hst, const vector<string> &words) {
        auto degenerate_case_index = degenerate_case_find(hst, words);
        if (degenerate_case_index)
            return *degenerate_case_index;

        vector<int> result;
        auto word_hashes = hash_all(words);
        auto sz = words.begin()->size();
        auto cnt = words.size();
        auto bound = hst.size() - cnt * sz + 1;
        const auto w_count_proto = initialize_w_count_map(words);

        for (int i = 0, h0 = 0; i != bound; ++i) {
            const int h = (i == 0) ? hash_one(hst.substr(0, sz))
                                   : rolling_hash(hst, h0, i, sz);

            if (word_hashes.count(h) &&
                stamping_match(hst, i, sz, w_count_proto))
                result.push_back(i);

            h0 = h;
        }

        return result;
    }

  private:
    static_assert(sizeof(char) < sizeof(int));
    static constexpr int base{numeric_limits<char>::max() + 1};
    static constexpr int bprime{10000019};
    static constexpr int max_word_size = 64;
    static const vector<int> modulo_pows;

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

    static unordered_set<int> hash_all(const vector<string> &words) {
        unordered_set<int> result;

        for (const string &w : words) {
            result.insert(hash_one(w));
        }

        return result;
    }

    static int rolling_hash(const string &s, const int prev_hash, const int i,
                            const int sz) {
        if (!i)
            return hash_one(s.substr(0, sz));

        const int leftmost{(modulo_pows[sz - 1] * int{s[i - 1]}) % bprime};
        const int head{modulo_minus(prev_hash, leftmost) * base};
        return (head + int{s[i + sz - 1]}) % bprime;
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

    static int hash_one(const string &s) {
        if (!s.size())
            return 0;

        return (hash_one(s.substr(0, s.size() - 1)) * base + int{s.back()}) %
               bprime;
    }

    static vector<int> precompute_modulo_pows(int power_bound) {
        vector<int> result(power_bound);

        for (int i = 0, value = 1; i != power_bound;
             ++i, value = (value * base) % bprime) {
            result[i] = value;
        }

        return result;
    }

    static int modulo_minus(int a, int b) {
        const int result = a - b;
        return result < 0 ? bprime + result : result;
    }
};

const vector<int> Solution::modulo_pows =
    Solution::precompute_modulo_pows(Solution::max_word_size);

void testcase1() {
    const string hst{"barfoothefoobarman"};
    const vector<string> words{"foo", "bar"};

    cout << hst << endl << words << endl;
    cout << Solution().findSubstring(hst, words) << endl << endl;
}

void testcase2() {
    const string hst{"wordgoodgoodgoodbestword"};
    const vector<string> words{"word", "good", "best", "word"};

    cout << hst << endl << words << endl;
    cout << Solution().findSubstring(hst, words) << endl << endl;
}

void testcase3() {
    const string hst{"wordgoodgoodgoodbestword"};
    const vector<string> words{"word", "good", "best", "good"};

    cout << hst << endl << words << endl;
    cout << Solution().findSubstring(hst, words) << endl << endl;
}

void testcase4() {
    const string hst{""};
    const vector<string> words{};

    cout << hst << endl << words << endl;
    cout << Solution().findSubstring(hst, words) << endl << endl;
}

void testcase5() {
    const string hst{"01234567"};
    const vector<string> words{"", "", ""};

    cout << hst << endl << words << endl;
    cout << Solution().findSubstring(hst, words) << endl << endl;
}

void testcase6() {
    const string hst{"aaaaaaaa"};
    const vector<string> words{"aa", "aa", "aa"};

    cout << hst << endl << words << endl;
    cout << Solution().findSubstring(hst, words) << endl << endl;
}

int main() {
    testcase1();
    testcase2();
    testcase3();
    testcase4();
    testcase5();
    testcase6();

    return 0;
}
