#include <bits/stdc++.h>
using namespace std;

template <typename T> T back(const set<T> &xs) { return *crbegin(xs); }
template <typename T> void pop_back(set<T> &xs) { xs.erase(prev(cend(xs))); }

vector<int> mark_subsequences(const string &bits) {
    const int n = bits.size();
    vector<int> ans(n, 0);
    set<int> ze_tails;
    set<int> on_tails;

    for (int i = 0; i < n; ++i) {
        if (bits[i] == '1') {
            if (ze_tails.empty()) {
                const auto id = on_tails.empty() ? 1 : (back(on_tails) + 1);
                ans[i] = id;
                on_tails.insert(id);
            } else {
                const auto id = back(ze_tails);
                ans[i] = id;
                pop_back(ze_tails);
                on_tails.insert(id);
            }
        } else {
            assert(bits[i] == '0');

            if (on_tails.empty()) {
                const auto id = ze_tails.empty() ? 1 : (back(ze_tails) + 1);
                ans[i] = id;
                ze_tails.insert(id);
            } else {
                const auto id = back(on_tails);
                ans[i] = id;
                pop_back(on_tails);
                ze_tails.insert(id);
            }
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string bits(n, ' ');
        cin >> bits;

        const auto ans = mark_subsequences(bits);
        cout << (*max_element(cbegin(ans), cend(ans))) << '\n';

        for (auto it = cbegin(ans); it != cend(ans); ++it) {
            if (it != cbegin(ans)) cout << ' ';
            cout << *it;
        }
        cout << '\n';
    }

    return 0;
}
