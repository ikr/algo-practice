#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int non_2_3_mul(int x) {
    while (x % 2 == 0) {
        x /= 2;
    }

    while (x % 3 == 0) {
        x /= 3;
    }

    return x;
}

vector<int> non_2_3_muls(const vector<int> &xs) {
    vector<int> result(sz(xs));
    transform(cbegin(xs), cend(xs), begin(result), non_2_3_mul);
    return result;
}

bool has_one_value(const vector<int> &xs) {
    return all_of(cbegin(xs), cend(xs),
                  [&](const int x) { return x == xs[0]; });
}

pii exps_of_2_3(int x) {
    int a{};
    int b{};

    while (x % 2 == 0) {
        x /= 2;
        ++a;
    }

    while (x % 3 == 0) {
        x /= 3;
        ++b;
    }

    return {a, b};
}

int ipow(const int b, const int e) {
    int result = 1;
    for (int i = 1; i <= e; ++i) {
        result *= b;
    }
    return result;
}

int min_ops(const vector<int> &xs) {
    if (has_one_value(non_2_3_muls(xs))) {
        vector<pii> es(sz(xs));
        transform(cbegin(xs), cend(xs), begin(es), exps_of_2_3);

        pii lo{INT_MAX, INT_MAX};
        for (const auto &[a, b] : es) {
            lo.first = min(lo.first, a);
            lo.second = min(lo.second, b);
        }

        int result{};
        for (const auto &[a, b] : es) {
            result += a - lo.first;
            result += b - lo.second;
        }
        return result;
    } else {
        return -1;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << min_ops(xs) << '\n';
    return 0;
}
