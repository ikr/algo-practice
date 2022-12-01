#include <bits/stdc++.h>
using namespace std;

template <typename T> struct mmax final {
    constexpr T operator()(const T &a, const T &b) const {
        return std::max(a, b);
    }
};

int main() {
    vector<vector<int>> xss(1);
    for (string line; getline(cin, line);) {
        if (line == "") {
            xss.push_back({});
            continue;
        }

        xss.back().push_back(stoi(line));
    }

    const auto result = transform_reduce(
        cbegin(xss), cend(xss), 0, mmax<int>{},
        [](const auto &xs) { return accumulate(cbegin(xs), cend(xs), 0); });

    cout << result << '\n';
    return 0;
}
