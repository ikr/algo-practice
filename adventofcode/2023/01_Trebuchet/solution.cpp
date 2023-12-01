#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

static vector<string> Nums{
    "zero",   "one",      "two",      "three",   "four",   "five",
    "six",    "seven",    "eight",    "nine",    "ten",    "eleven",
    "twelve", "thirteen", "fourteen", "fifteen", "sixteen"};

pair<int, int> edge_nums(const string &s) {
    map<int, int> ltr;
    map<int, int> rtl;

    for (int j = 0; j < 10; ++j) {
        const auto i = s.find(chof('0' + j));
        if (i != string::npos) ltr.emplace(inof(i), j);

        const auto k = s.rfind(chof('0' + j));
        if (k != string::npos) rtl.emplace(inof(k), j);
    }

    for (int j = 0; j < sz(Nums); ++j) {
        const auto i = s.find(Nums[j]);
        if (i != string::npos) ltr.emplace(inof(i), j);

        const auto k = s.rfind(Nums[j]);
        if (k != string::npos) rtl.emplace(inof(k), j);
    }

    assert(!empty(ltr));
    assert(!empty(rtl));
    return {cbegin(ltr)->second, crbegin(rtl)->second};
}

int main() {
    int result{};
    for (string line; getline(cin, line);) {
        const auto [a, b] = edge_nums(line);
        const auto cur = to_string(a) + to_string(b);
        result += stoi(string{cur[0], cur.back()});
    }
    cout << result << '\n';
    return 0;
}
