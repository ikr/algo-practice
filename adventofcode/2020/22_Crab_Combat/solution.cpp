#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const deque<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

template <typename T> constexpr int intof(const T x) {
    return static_cast<int>(x);
}

enum class Winner { X, Y };

int score(const deque<int> &xs) {
    const int n = xs.size();
    vector fs(n, 0);
    iota(begin(fs), end(fs), 1);
    reverse(begin(fs), end(fs));
    return inner_product(cbegin(xs), cend(xs), cbegin(fs), 0);
}

pair<Winner, deque<int>> play(deque<int> xs, deque<int> ys) {
    set<deque<int>> x_states;
    set<deque<int>> y_states;

    while (!xs.empty() && !ys.empty()) {
        const int x = xs.front();
        xs.pop_front();

        const int y = ys.front();
        ys.pop_front();

        const Winner winner = [&]() {
            if (intof(xs.size()) >= x && intof(ys.size()) >= y) {
                const auto [ans, _] = play(xs, ys);
                return ans;
            }

            return x > y ? Winner::X : Winner::Y;
        }();

        if (winner == Winner::X) {
            xs.push_back(x);
            xs.push_back(y);
        } else {
            ys.push_back(y);
            ys.push_back(x);
        }

        if (x_states.count(xs) || y_states.count(ys)) {
            return {Winner::X, xs};
        }

        x_states.insert(xs);
        y_states.insert(ys);
    }

    return xs.empty() ? pair{Winner::Y, ys} : pair{Winner::X, xs};
}

int solve(const deque<int> &xs, const deque<int> &ys) {
    const auto [_, zs] = play(xs, ys);
    return score(zs);
}

int main() {
    deque<int> xs;
    deque<int> ys;

    bool one = true;
    for (string line; getline(cin, line);) {
        if (line == "Player 1:") continue;
        if (line == "") {
            continue;
        }
        if (line == "Player 2:") {
            one = false;
            continue;
        }

        const int n = stoi(line);
        if (one) {
            xs.push_back(n);
        } else {
            ys.push_back(n);
        }
    }

    cout << solve(xs, ys) << '\n';
    return 0;
}
