#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int score(const char c) {
    const map<char, int> table{{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
    return table.at(c);
}

const optional<char> first_incorrect_closer(const string &xs) {
    stack<char> st;

    const auto top_matches = [&](const char x) -> bool {
        return !st.empty() && st.top() == x;
    };

    for (const auto x : xs) {
        switch (x) {
        case ')':
            if (top_matches('(')) {
                st.pop();
                break;
            } else {
                return x;
            }

        case ']':
            if (top_matches('[')) {
                st.pop();
                break;
            } else {
                return x;
            }

        case '}':
            if (top_matches('{')) {
                st.pop();
                break;
            } else {
                return x;
            }

        case '>':
            if (top_matches('<')) {
                st.pop();
                break;
            } else {
                return x;
            }

        default:
            st.push(x);
        }
    }

    return nullopt;
}

int main() {
    int ans{};
    for (string line; getline(cin, line);) {
        const auto x = first_incorrect_closer(line);
        if (x) {
            ans += score(*x);
        }
    }

    cout << ans << '\n';
    return 0;
}
