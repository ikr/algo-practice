#include <bits/stdc++.h>
using namespace std;

template <typename T> string join(const string &glue, const vector<T> &tokens) {
    string ans;

    for (const auto &t : tokens) {
        if (!ans.empty()) ans += glue;
        ans += t;
    }

    return ans;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_keypresses(const string &xs) {
    const auto n = sz(xs);
    bool caps = false;
    int result{};

    for (int i = 0; i < n; ++i) {
        if (xs[i] == ' ') {
            ++result;
            continue;
        }

        if (isupper(xs[i], locale::classic())) {
            if (caps) {
                ++result;
            } else {
                if (i < n - 1 && isupper(xs[i + 1], locale::classic())) {
                    caps = true;
                }
                result += 2;
            }
        } else {
            assert(islower(xs[i], locale::classic()));
            if (caps) {
                ++result;
                caps = false;
            }
            ++result;
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<string> words(n);
    for (auto &word : words) cin >> word;
    const auto xs = join(" ", words);
    cout << min_keypresses(xs) << '\n';
    return 0;
}
