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

int count_unique_chars(const vector<string> &ss) {
    set<char> ans;

    for (const auto &s : ss) {
        ans.insert(cbegin(s), cend(s));
    }

    return ans.size();
}

int process_groups(const vector<vector<string>> &groups) {
    return ttransform_reduce(cbegin(groups), cend(groups), 0, plus<int>{},
                             count_unique_chars);
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
