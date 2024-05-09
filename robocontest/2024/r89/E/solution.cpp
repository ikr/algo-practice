#include <bits/stdc++.h>
using namespace std;

static const double Eps = 0.01;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

double angle_between_hands(const double ih, const double im, const double is) {
    const double m = (360.0 / 60.0) * im + 6.0 * (is / 60.0);
    const double h = (360.0 / 12.0) * ih + 30.0 * (im / 60.0);

    auto result = abs(h - m);
    if (result > 180.0) {
        result = 360 - result;
    }
    return result;
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }
vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(2) << fixed;

    string src;
    cin >> src;

    const auto parts = split(":", src);

    const double ih0 = stoi(parts[0]) % 12;
    const double im0 = stoi(parts[1]);

    for (int ds = 0;; ++ds) {
        const double is = ds % 60;
        const double im = im0 + doof(ds / 60);
        const double ih = ih0 + doof((ds / 60) / 60);
        const auto angle0 = angle_between_hands(ih, im, is);

        if (angle0 < Eps) {
            const int ds_ = ds + 1;
            const double is_ = ds_ % 60;
            const double im_ = im0 + doof(ds_ / 60);
            const double ih_ = ih0 + doof((ds_ / 60) / 60);
            const auto angle1 = angle_between_hands(ih_, im_, is_);

            if (angle1 < angle0) {
                cout << ds_ << '\n';
            } else {
                cout << ds << '\n';
            }
            break;
        }
    }
    return 0;
}
