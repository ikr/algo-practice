#include <bits/stdc++.h>

using namespace std;

using sz_t = unsigned long long;
constexpr sz_t npos{string::npos};

string remove_single_vs(const string &s) {
    sz_t i = s.find("ovo");
    unordered_set<sz_t> to_skip;

    while (i != npos) {
        to_skip.insert(i + 1);
        i = s.find("ovo", i + 2);
    }

    string ans;
    for (sz_t i = 0; i != s.size(); ++i) {
        if (!to_skip.count(i)) ans += s[i];
    }

    return ans;
}

sz_t count_variants(const vector<sz_t> &wo_counts) {
    const sz_t sz = wo_counts.size();

    unordered_map<sz_t, sz_t> partial_ws_sum{{sz - 1, wo_counts.back()}};
    for (int i = sz - 3; i >= 0; i -= 2) {
        partial_ws_sum[i] = wo_counts[i] + partial_ws_sum[i + 2];
    }

    sz_t multiplier = wo_counts[sz - 2] * wo_counts[sz - 1];
    sz_t ans = wo_counts[sz - 3] * multiplier;

    for (int i = sz - 5; i >= 0; i -= 2) {
        multiplier += wo_counts[i + 1] * partial_ws_sum[i + 2];
        ans += wo_counts[i] * multiplier;
    }

    return ans;
}

int main() {
    string s;
    cin >> s;

    s = remove_single_vs(s);

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

    cout << count_variants(wo_counts) << '\n';
    return 0;
}
