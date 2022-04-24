#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string reverse_pair(const string &p) {
    assert(sz(p) == 2);
    return string{p[1], p[0]};
}

pair<map<string, int>, map<string, int>> build_index(const vector<string> &ps) {
    map<string, int> idx0;
    map<string, int> idx1;

    for (const auto p : ps) {
        ++idx0[p];
        ++idx1[reverse_pair(p)];
    }

    return {idx0, idx1};
}

static const vector<char> AK{'a', 'b', 'c', 'd', 'e', 'f',
                             'g', 'h', 'i', 'j', 'k'};

vector<string> variations_of(const string &p, const int i) {
    assert(0 <= i && i < 3);
    vector<string> result;

    for (const auto c : AK) {
        if (c == p[i]) continue;
        auto p_ = p;
        p_[i] = c;
        result.push_back(p_);
    }

    return result;
}

ll num_pairs(const vector<string> &ps) {
    auto [idx0, idx1] = build_index(ps);
    ll result{};

    for (const auto p : ps) {
        for (const auto i : vector{0, 1}) {
            for (const auto &p_ : variations_of(p, i)) {
                result += idx0[p_];
            }
        }
    }

    return result / 2LL;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<string> ps(n);
        for (auto &p : ps) cin >> p;

        cout << num_pairs(ps) << '\n';
    }

    return 0;
}
