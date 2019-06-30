#include <bits/stdc++.h>

using namespace std;

using CountsV = array<int, 'z' - 'a' + 1>;
template <typename T> int intof(const T x) { return static_cast<int>(x); }

template <typename T>
ostream &operator<<(ostream &os, const array<T, 'z' - 'a' + 1> &xs) {
    for (const auto x : xs) {
        cout << x << ' ';
    }

    return os;
}

bool is_letters_subset(const CountsV &candidate, const CountsV &master) {
    for (int i = 0; i != master.size(); ++i) {
        if (candidate.at(i) > master.at(i)) return false;
    }

    return true;
}

CountsV make_counts(const string &s) {
    CountsV ans{};

    for (const char c : s) {
        ++ans[c - 'a'];
    }

    return ans;
}

int main() {
    int s_sz;
    cin >> s_sz;

    string s;
    cin >> s;

    vector<CountsV> counts_by_sz(s.size() + 1);

    for (int i = 0; i != intof(s.size()); ++i) {
        const CountsV &prev_counts_v = counts_by_sz[i];

        CountsV counts_v = prev_counts_v;
        ++counts_v[s[i] - 'a'];

        counts_by_sz[i + 1] = counts_v;
    }

    int friends_count;
    cin >> friends_count;

    for (int i = 0; i != friends_count; ++i) {
        string name;
        cin >> name;

        if (name.size() == 1) {
            cout << s.find(name) + 1 << '\n';
        } else {
            const auto name_counts = make_counts(name);

            const auto it =
                upper_bound(counts_by_sz.cbegin(), counts_by_sz.cend(),
                            name_counts, [](const auto &xs, const auto &ys) {
                                return is_letters_subset(xs, ys);
                            });

            cout << distance(counts_by_sz.cbegin(), it) << '\n';
        }
    }
}
