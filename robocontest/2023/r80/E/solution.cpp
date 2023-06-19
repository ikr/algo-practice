#include <bits/stdc++.h>
using namespace std;

using Box = array<array<int, 3>, 3>;

static const Box Dst{array{1, 2, 3}, array{4, 5, 6}, array{7, 8, 9}};

string box_to_code(const Box &b) {
    string result;
    for (int ro = 0; ro < 3; ++ro) {
        for (int co = 0; co < 3; ++co) {
            result += to_string(b[ro][co]);
        }
    }
    return result;
}

Box code_to_box(const string &c) {
    return Box{array{c[0] - '0', c[1] - '0', c[2] - '0'},
               array{c[3] - '0', c[4] - '0', c[5] - '0'},
               array{c[6] - '0', c[7] - '0', c[8] - '0'}};
}

vector<string> adjacent_codes(unordered_map<string, int> &D, const string &c) {
    vector<string> result;

    {
        auto x = c;
        swap(x[0], x[1]);
        if (!D.count(x)) result.push_back(x);
    }

    {
        auto x = c;
        swap(x[0], x[3]);
        if (!D.count(x)) result.push_back(x);
    }

    {
        auto x = c;
        swap(x[1], x[4]);
        if (!D.count(x)) result.push_back(x);
    }

    {
        auto x = c;
        swap(x[1], x[2]);
        if (!D.count(x)) result.push_back(x);
    }

    {
        auto x = c;
        swap(x[2], x[5]);
        if (!D.count(x)) result.push_back(x);
    }

    {
        auto x = c;
        swap(x[3], x[6]);
        if (!D.count(x)) result.push_back(x);
    }

    {
        auto x = c;
        swap(x[3], x[4]);
        if (!D.count(x)) result.push_back(x);
    }

    {
        auto x = c;
        swap(x[4], x[7]);
        if (!D.count(x)) result.push_back(x);
    }

    {
        auto x = c;
        swap(x[4], x[5]);
        if (!D.count(x)) result.push_back(x);
    }

    {
        auto x = c;
        swap(x[5], x[8]);
        if (!D.count(x)) result.push_back(x);
    }

    {
        auto x = c;
        swap(x[6], x[7]);
        if (!D.count(x)) result.push_back(x);
    }

    {
        auto x = c;
        swap(x[7], x[8]);
        if (!D.count(x)) result.push_back(x);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    Box Src{};
    for (auto &row : Src) {
        for (auto &x : row) cin >> x;
    }
    const auto src = box_to_code(Src);
    const auto dst = box_to_code(Dst);

    unordered_map<string, int> D;
    D[box_to_code(Src)] = 0;

    queue<string> q;
    q.push(src);

    while (!D.count(dst)) {
        const auto u = q.front();
        q.pop();

        for (const auto &v : adjacent_codes(D, u)) {
            D[v] = D.at(u) + 1;
            q.push(v);
        }
    }

    cout << D.at(dst) << '\n';
    return 0;
}
