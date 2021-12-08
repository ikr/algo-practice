#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim, const string &s) {
    regex r(delim);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

int easy_digits_num(const vector<vector<string>> &all_out_vals) {
    return transform_reduce(
        cbegin(all_out_vals), cend(all_out_vals), 0, plus<int>{},
        [](const auto &ovs) {
            return count_if(cbegin(ovs), cend(ovs), [](const auto &ov) {
                return (2 <= sz(ov) && sz(ov) <= 4) || sz(ov) == 7;
            });
        });
}

int main() {
    vector<vector<string>> all_out_vals;

    for (string line; getline(cin, line);) {
        const auto parts = split(" \\| ", line);
        assert(sz(parts) == 2);
        const auto ovs = split(" ", parts[1]);
        all_out_vals.push_back(ovs);
    }

    cout << easy_digits_num(all_out_vals) << '\n';
    return 0;
}
