#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi next_sig(vi ds) {
    for (int i = sz(ds) - 2; i >= 0; --i) {
        if (ds[i]) {
            --ds[i];
            ++ds[i + 1];
            break;
        }
    }

    return ds;
}

string encode(const string &xs, const vi &ds) {
    string ans;

    for (int i = 0; i < sz(xs); ++i) {
        if (ds[i]) {
            ans += string(ds[i], xs[i]);
        }
    }

    return ans;
}

struct DistinctStrings final {
    vector<string> generate(const int L, string xs, const int N) const {
        sort(begin(xs), end(xs));

        vi ds;

        const auto reset_ds = [&]() {
            ds = vi(sz(xs), 0);
            ds[0] = L;
        };

        reset_ds();

        vector<string> ans;
        for (int i = 0; i < N; ++i) {
            ans.push_back(encode(xs, ds));
            const auto ds_ = next_sig(ds);

            if (ds_ == ds) {
                next_permutation(begin(xs), end(xs));
                reset_ds();
                --i;
                continue;
            }

            ds = ds_;
        }

        return ans;
    }
};

template <typename T>
constexpr typename vector<T>::const_iterator cbegin(const vector<T> &xs) {
    return xs.cbegin();
}

template <typename T>
constexpr typename vector<T>::const_iterator cend(const vector<T> &xs) {
    return xs.cend();
}

template <typename T> bool are_all_of_length(const vector<T> &xs, const int l) {
    return all_of(cbegin(xs), cend(xs),
                  [l](const auto &x) { return sz(x) == l; });
}

template <typename T> bool are_all_distinct(const vector<T> &xs) {
    return sz(set<string>(cbegin(xs), cend(xs))) == sz(xs);
}

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DistinctStrings{}.generate(5, "qwertyuiopasdfghjklzxcvbnm", 10);
        EXPECT(sz(actual) == 10);
        EXPECT(are_all_of_length(actual, 5));
        EXPECT(are_all_distinct(actual));
    },
    CASE("Example 1") {
        const auto actual = DistinctStrings{}.generate(3, "ABCDE02468", 17);
        EXPECT(sz(actual) == 17);
        EXPECT(are_all_of_length(actual, 3));
        EXPECT(are_all_distinct(actual));
    },
    CASE("Short A") {
        const auto actual = DistinctStrings{}.generate(3, "0123456789", 200);
        EXPECT(sz(actual) == 200);
        EXPECT(are_all_of_length(actual, 3));
        EXPECT(are_all_distinct(actual));
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
