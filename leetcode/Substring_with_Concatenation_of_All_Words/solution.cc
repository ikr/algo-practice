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
            return vector<int>{*degenerate_case_index};

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
    static_assert(sizeof(char) < sizeof(int));
    static_assert(sizeof(int) < sizeof(long));
    static constexpr int base{numeric_limits<char>::max() + 1};
    static constexpr int bprime{10000019};

    static optional<int> degenerate_case_find(const string &hst,
                                              const vector<string> &words) {
        if (!words.size())
            return {0};

        if (!words.begin()->size())
            return {0};

        if (hst.size() < words.size() * words.begin()->size())
            return {-1};

        if (words.size() == 1 && words.begin()->size() == hst.size())
            return {*words.begin() == hst ? 0 : -1};

        return nullopt;
    }

    static unordered_set<int> hash_all(const vector<string> &words) {
        unordered_set<int> result;

        for (const string &w : words) {
            result.insert(hash_one(w));
        }

        return result;
    }

    static unordered_set<string> make_set(const vector<string> &words) {
        unordered_set<string> result;

        for (const string &w : words) {
            result.insert(w);
        }

        return result;
    }

    static int rolling_hash(const string &s, const int prev_hash, const int i,
                            const int sz) {
        if (!i)
            return hash_one(s.substr(0, sz));

        const long leftmost{(modulo_pow(base, sz - 1) * int{s[i - 1]}) %
                            bprime};
        const long head{(prev_hash - leftmost) * base};

        return static_cast<int>((head + long{s[i + sz - 1]}) % bprime);
    }

    static bool stamping_match(const string &hst, int i,
                               const vector<string> &words) {
        const int sz = words.begin()->size();
        unordered_map<string, int> w_count;
        for (const string &w : words) {
            ++w_count[w];
        }

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

    static int hash_one(const string &s) {
        if (!s.size())
            return 0;

        return (hash_one(s.substr(0, s.size() - 1)) * base + int{s.back()}) %
               bprime;
    }

    static int modulo_pow(int base, int power) {
        if (!power)
            return 1;

        if (power % 2) {
            return static_cast<int>((long{base} * modulo_pow(base, power - 1)) %
                                    bprime);
        }

        const long sqr{modulo_pow(base, power / 2)};
        return static_cast<int>((sqr * sqr) % bprime);
    }
};

int main() {
    Solution s;
    const string hst{"barfoothefoobarman"};
    const vector<string> words{"foo", "bar"};

    cout << hst << endl << words << endl;
    cout << s.findSubstring(hst, words) << endl;

    return 0;
}
