#include <bits/stdc++.h>

using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (const auto x : xs) {
        os << x << ' ';
    }

    return os;
}

using sz_t = string::size_type;
constexpr sz_t npos{string::npos};

void remove_single_vs(string &s) {
    sz_t i = s.find("ovo");

    while (i != npos) {
        s.erase(i + 1, 1);
        i = s.find("ovo", i);
    }
}

int main() {
    string s;
    cin >> s;

    remove_single_vs(s);

    vector<sz_t> wo_counts;
    bool counting_ws = true;

    for (sz_t i = 0; i != npos && i != s.size();) {
        if (counting_ws) {
            i = s.find("vv", i);

            if (i != npos) {
                int w_count = 1;
                i += 2;

                while (i != s.size() && s.at(i) == 'v') {
                    ++w_count;
                    ++i;
                }

                wo_counts.push_back(w_count);
            }

            counting_ws = false;
        } else {
            i = s.find('o', i);

            if (i != npos) {
                int o_count = 1;
                ++i;

                while (i != s.size() && s.at(i) == 'o') {
                    ++o_count;
                    ++i;
                }

                wo_counts.push_back(o_count);
            }

            counting_ws = true;
        }
    }

    if (wo_counts.size() < 3) {
        cout << "0\n";
        return 0;
    }

    if (wo_counts.size() % 2 == 0) {
        wo_counts.pop_back();
    }

    cout << wo_counts << '\n';

    sz_t ans = 0;

    for (size_t prefix = 0; prefix <= wo_counts.size() - 3; prefix += 2) {
        for (size_t infix = prefix + 1; infix <= wo_counts.size() - 2;
             infix += 2) {
            for (size_t suffix = infix + 1; suffix <= wo_counts.size() - 1;
                 suffix += 2) {
                ans += wo_counts[prefix] * wo_counts[infix] * wo_counts[suffix];
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
