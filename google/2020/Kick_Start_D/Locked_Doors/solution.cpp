#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vi inc_all(vi xs) {
    for (auto &x : xs) ++x;
    return xs;
}

vi rooms_order(const vi &doors, const int start) {
    vi ans{start};
    pi span{start, start};
    const int sz = doors.size() + 1;

    while (span.first != 0 || span.second != sz - 1) {
        if (span.first != 0 && span.second != sz - 1) {
            if (doors[span.first - 1] < doors[span.second]) {
                ans.push_back(span.first - 1);
                --span.first;
            } else {
                ans.push_back(span.second + 1);
                ++span.second;
            }

            continue;
        }

        if (span.first != 0) {
            ans.push_back(span.first - 1);
            --span.first;
        } else {
            assert(span.second != sz - 1);
            ans.push_back(span.second + 1);
            ++span.second;
        }
    }

    return ans;
}

vi query_results(const vi &doors, const vpi &queries) {
    vi ans;
    unordered_map<int, vi> memo;

    for (const auto q : queries) {
        if (!memo.count(q.first)) memo[q.first] = rooms_order(doors, q.first);
        ans.push_back(memo[q.first][q.second]);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int rooms_num, queries_num;
        cin >> rooms_num >> queries_num;

        vi doors(rooms_num - 1, 0);
        for (auto &d : doors) cin >> d;

        vpi queries(queries_num, {0, 0});
        for (auto &q : queries) {
            cin >> q.first >> q.second;
            --q.first;
            --q.second;
        }

        cout << "Case #" << i << ": " << inc_all(query_results(doors, queries))
             << '\n';
    }

    return 0;
}
