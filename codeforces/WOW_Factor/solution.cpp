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

int main() {
    string s;
    cin >> s;

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

    cout << wo_counts << '\n';
}
