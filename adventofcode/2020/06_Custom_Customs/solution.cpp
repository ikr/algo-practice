#include <bits/stdc++.h>
using namespace std;

template <typename Iter, typename R, typename Binop, typename Unaop>
R ttransform_reduce(Iter first, Iter last, R init, Binop binop, Unaop unaop) {
    R ans = init;

    for (auto it = first; it != last; ++it) {
        ans = binop(ans, unaop(*it));
    }

    return ans;
}

int count_omnipresent_chars(const vector<string> &ss) {
    const int sz = 'z' - 'a' + 1;
    vector<int> freqs(sz, 0);

    for (const auto &s : ss) {
        for (const char c : s) ++freqs[c - 'a'];
    }

    const int n = ss.size();
    return count_if(cbegin(freqs), cend(freqs),
                    [n](const int f) { return f == n; });
}

int process_groups(const vector<vector<string>> &groups) {
    return ttransform_reduce(cbegin(groups), cend(groups), 0, plus<int>{},
                             count_omnipresent_chars);
}

int main() {
    vector<vector<string>> groups(1);

    for (string line; getline(cin, line);) {
        if (line == "" && !groups.back().empty()) {
            groups.push_back({});
            continue;
        }

        groups.back().push_back(line);
    }

    if (groups.back().empty()) groups.pop_back();

    cout << process_groups(groups) << '\n';
    return 0;
}
