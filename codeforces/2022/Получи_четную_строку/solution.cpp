#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;
constexpr int az_to_i(const char c) {
    return static_cast<int>(c) - static_cast<int>('a');
}

vector<vector<int>> indices_by_letter(const string &xs) {
    vector<vector<int>> result(AZ);
    for (int i = 0; i < sz(xs); ++i) {
        result[az_to_i(xs[i])].push_back(i);
    }
    return result;
}

int min_ops(const string &xs) {
    const auto idx = indices_by_letter(xs);

    const auto pair_index = [&](const int i) -> optional<int> {
        const auto &ii = idx[az_to_i(xs[i])];
        const auto it = upper_bound(cbegin(ii), cend(ii), i);
        if (it == cend(ii)) return nullopt;
        assert(i < *it);
        return *it;
    };

    const auto pair_has_other_pair_in_between = [&](const int i,
                                                    const int j) -> bool {
        assert(xs[i] == xs[j]);
        for (int k = 0; k < AZ; ++k) {
            if (k == az_to_i(xs[i])) continue;

            const auto &iik = idx[k];
            const auto it = upper_bound(cbegin(iik), cend(iik), i);
            if (it == cend(iik) || next(it) == cend(iik)) continue;
            assert(i < *it);
            assert(*it < *next(it));
            if (*next(it) < j) return true;
        }

        return false;
    };

    int result{};

    for (int i = 0; i < sz(xs);) {
        if (i < sz(xs) - 1) {
            if (xs[i] == xs[i + 1]) {
                i += 2;
            } else {
                const auto pj = pair_index(i);
                if (pj) {
                    if (pair_has_other_pair_in_between(i, *pj)) {
                        ++result;
                        ++i;
                    } else {
                        result += *pj - i - 1;
                        i = *pj + 1;
                    }
                } else {
                    ++result;
                    ++i;
                }
            }
        } else {
            ++result;
            ++i;
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << min_ops(xs) << '\n';
    }

    return 0;
}
