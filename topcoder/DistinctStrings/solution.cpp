#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr typename vector<T>::const_iterator cbegin(const vector<T> &xs) {
    return xs.cbegin();
}

template <typename T>
constexpr typename vector<T>::const_iterator cend(const vector<T> &xs) {
    return xs.cend();
}

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

string corresponding(const string &xs, const vi &ds) {
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
            ans.push_back(corresponding(xs, ds));
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

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DistinctStrings{}.generate(5, "qwertyuiopasdfghjklzxcvbnm", 10);
        const vector<string> expected{"hello", "abcde", "wwwww", "coins", "coder", "digit", "clash", "qwert", "puppy", "kitty"};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = DistinctStrings{}.generate(3, "ABCDE02468", 17);
        const vector<string> expected{"ABC", "D2E", "DDD", "AAA", "EEE", "024", "042", "204", "240", "402", "420", "4AB", "4EE", "E4E", "ED4", "868", "844"};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
