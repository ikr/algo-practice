#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const pair<optional<char>, stack<char>>
first_incorrect_closer_and_end_stack(const string &xs) {
    stack<char> st;

    const auto top_matches = [&](const char x) -> bool {
        return !st.empty() && st.top() == x;
    };

    for (const auto x : xs) {
        switch (x) {
        case ')':
            if (top_matches('(')) {
                st.pop();
                break;
            } else {
                return {x, st};
            }

        case ']':
            if (top_matches('[')) {
                st.pop();
                break;
            } else {
                return {x, st};
            }

        case '}':
            if (top_matches('{')) {
                st.pop();
                break;
            } else {
                return {x, st};
            }

        case '>':
            if (top_matches('<')) {
                st.pop();
                break;
            } else {
                return {x, st};
            }

        default:
            st.push(x);
        }
    }

    return {nullopt, st};
}

string closing_brackets(stack<char> st) {
    string result;
    while (!st.empty()) {
        const auto x = st.top();
        st.pop();

        switch (x) {
        case '(':
            result += ')';
            break;
        case '[':
            result += ']';
            break;
        case '{':
            result += '}';
            break;
        case '<':
            result += '>';
            break;
        default:
            assert(false && "/o\\");
        }
    }
    return result;
}

ll char_score(const char c) {
    const map<char, int> table{{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
    return table.at(c);
}

ll score(const string &xs) {
    return accumulate(cbegin(xs), cend(xs), 0LL,
                      [](const ll agg, const char x) -> ll {
                          return agg * 5 + char_score(x);
                      });
}

int main() {
    vector<ll> ss;

    for (string line; getline(cin, line);) {
        const auto [x, st] = first_incorrect_closer_and_end_stack(line);
        if (x) continue;

        ss.push_back(score(closing_brackets(st)));
    }

    sort(begin(ss), end(ss));
    cout << ss[ss.size() / 2] << '\n';
    return 0;
}
