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

template <typename Iter1, typename Iter2, typename F>
void closest_dom_indices(const Iter1 in_first, const Iter1 in_last, Iter2 out,
                         const F as_index) {
    stack<Iter1> st;
    for (auto it = in_first; it != in_last; ++it, ++out) {
        while (!st.empty() && *st.top() < *it) st.pop();
        *out = st.empty() ? -1 : as_index(st.top());
        st.push(it);
    }
}

vi gather_ltr_dom_indices(const vi &doors) {
    vi ans(doors.size(), -1);
    closest_dom_indices(
        cbegin(doors), cend(doors), begin(ans),
        [&doors](const auto it) -> int { return distance(cbegin(doors), it); });
    return ans;
}

vi gather_rtl_dom_indices(const vi &doors) {
    vi ans(doors.size(), -1);
    closest_dom_indices(crbegin(doors), crend(doors), rbegin(ans),
                        [&doors](const auto it) -> int {
                            return doors.size() - 1 -
                                   distance(crbegin(doors), it);
                        });
    return ans;
}

vi gather_dom_indices(const vi &doors) {
    const auto ltr = gather_ltr_dom_indices(doors);
    const auto rtl = gather_rtl_dom_indices(doors);

    vi ans(doors.size(), -1);
    transform(cbegin(ltr), cend(ltr), cbegin(rtl), begin(ans),
              [&doors](const int i, const int j) -> int {
                  const int x = i == -1 ? INT_MAX : doors[i];
                  const int y = j == -1 ? INT_MAX : doors[j];
                  return x < y ? i : j;
              });
    return ans;
}

int kth_room(const vi &doors, const int s, const int k) { return s; }

vi query_results(const vi &doors, const vpi &queries) {
    gather_dom_indices(doors);
    vi ans(queries.size());

    transform(
        cbegin(queries), cend(queries), begin(ans),
        [&doors](const pi &q) { return kth_room(doors, q.first, q.second); });

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
