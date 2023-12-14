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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
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

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

ostream &operator<<(ostream &os, const vector<string> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> transpose(const vector<string> &m) {
    const auto H = sz(m[0]);
    const auto W = sz(m);

    vector<string> ans(H, string(W, ' '));
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            ans[ro][co] = m[co][ro];
        }
    }
    return ans;
}

void roll_west(string &xs) {
    const auto slide_left = [&](int i) {
        assert(xs[i] == 'O');
        for (;;) {
            if (i == 0 || xs[i - 1] != '.') return;
            swap(xs[i], xs[i - 1]);
            --i;
        }
    };

    int i = 0;
    for (;;) {
        const auto is = xs.find('O', i);
        if (is == string::npos) return;
        slide_left(inof(is));
        ++i;
    }
}

void roll_east(string &xs) {
    ranges::reverse(xs);
    roll_west(xs);
    ranges::reverse(xs);
}

void roll_all_west(vector<string> &grid) {
    for (auto &row : grid) roll_west(row);
}

void roll_all_east(vector<string> &grid) {
    for (auto &row : grid) roll_east(row);
}

void roll_all_north(vector<string> &grid) {
    grid = transpose(grid);
    roll_all_west(grid);
    grid = transpose(grid);
}

void roll_all_south(vector<string> &grid) {
    grid = transpose(grid);
    roll_all_east(grid);
    grid = transpose(grid);
}

int total_load_west(const vector<string> &grid) {
    const auto W = sz(grid[0]);
    int result{};
    for (auto &row : grid) {
        for (int co = 0; co < W; ++co) {
            if (row[co] == 'O') {
                result += W - co;
            }
        }
    }
    return result;
}

int total_load_north(vector<string> grid) {
    grid = transpose(grid);
    return total_load_west(grid);
}

int total_load_east(const vector<string> &grid) {
    const auto W = sz(grid[0]);
    int result{};
    for (auto &row : grid) {
        for (int co = 0; co < W; ++co) {
            if (row[co] == 'O') {
                result += co + 1;
            }
        }
    }
    return result;
}

int total_load_south(vector<string> grid) {
    grid = transpose(grid);
    return total_load_east(grid);
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) grid.push_back(line);

    for (int i = 1; i <= 3; ++i) {
        roll_all_north(grid);
        roll_all_west(grid);
        roll_all_south(grid);
        roll_all_east(grid);
        cerr << grid << endl << endl;
    }

    return 0;
}
