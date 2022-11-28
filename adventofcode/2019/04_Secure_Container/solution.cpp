#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

template <typename T> vector<int> digits_reversed(T n) {
    vector<int> ans;

    while (n) {
        ans.push_back(inof(n % static_cast<T>(10)));
        n /= static_cast<T>(10);
    }

    return ans;
}

template <typename T> vector<int> digits(T n) {
    auto ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

bool is_monotonic(const vector<int> &xs) {
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i - 1] > xs[i]) return false;
    }
    return true;
}

bool has_strict_pair(const vector<int> &xs) {
    for (int i = 1; i < sz(xs); ++i) {
        const auto left = (i - 2 >= 0) ? xs[i - 2] : INT_MIN;
        const auto right = (i + 1 < sz(xs)) ? xs[i + 1] : INT_MIN;
        if (left != xs[i - 1] && xs[i - 1] == xs[i] && xs[i] != right) {
            return true;
        }
    }
    return false;
}

int potential_passwords_count(const int A, const int B) {
    int result{};
    for (int x = A; x <= B; ++x) {
        const auto ds = digits(x);
        result += is_monotonic(ds) && has_strict_pair(ds);
    }
    return result;
}

int main() {
    string line;
    cin >> line;

    const auto parts = split("-", line);
    const auto A = stoi(parts[0]);
    const auto B = stoi(parts[1]);

    cout << potential_passwords_count(A, B) << '\n';
    return 0;
}
