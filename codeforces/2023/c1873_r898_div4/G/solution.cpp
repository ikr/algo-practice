#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<char, int>> run_length_encode(const string &xs) {
    vector<pair<char, int>> ans{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == ans.back().first) {
            ++(ans.back().second);
        } else {
            ans.emplace_back(xs[i], 1);
        }
    }
    return ans;
}

int max_coins(const string &xs) {
    auto rle = run_length_encode(xs);
    cerr << rle << endl;
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < sz(rle); ++i) {
        if (rle[i].first == 'A') pq.emplace(rle[i].second, i);
    }

    int result{};

    while (!empty(pq)) {
        const auto [f, i] = pq.top();
        cerr << "f:" << f << " i:" << i << endl;
        pq.pop();

        if (i && rle[i - 1].first == 'B' && rle[i - 1].second) {
            --rle[i - 1].second;
            result += f;
        } else if (i < sz(rle) - 1 && rle[i + 1].first == 'B' &&
                   rle[i + 1].second) {
            --rle[i + 1].second;
            result += f;
        }
        cerr << rle << endl;
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << max_coins(xs) << '\n';
    }

    return 0;
}
