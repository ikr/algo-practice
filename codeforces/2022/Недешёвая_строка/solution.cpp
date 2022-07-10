#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;

vector<int> freqs(const string &xs) {
    vector<int> result(AZ, 0);
    for (const auto x : xs) {
        ++result[inof(x) - inof('a')];
    }
    return result;
}

int total_price(const vector<int> &fs) {
    int result{};
    for (int i = 0; i < AZ; ++i) {
        const auto m = i + 1;
        result += m * fs[i];
    }
    return result;
}

vector<int> removal_plan(vector<int> fs, const int t) {
    auto s = total_price(fs);
    vector<int> result(AZ, 0);

    while (s > t) {
        for (int i = AZ - 1; i >= 0; --i) {
            if (fs[i]) {
                s -= i + 1;
                --fs[i];
                ++result[i];
                break;
            }
        }
    }

    return result;
}

string longest_remaining(const string &xs, const int p) {
    auto rfs = removal_plan(freqs(xs), p);

    string result;
    for (const auto x : xs) {
        const auto i = inof(x) - inof('a');
        if (rfs[i]) {
            --rfs[i];
        } else {
            result += x;
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

        int p;
        cin >> p;

        cout << longest_remaining(xs, p) << '\n';
    }

    return 0;
}
