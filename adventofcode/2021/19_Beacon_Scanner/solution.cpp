#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const vector<array<T, N>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
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

using Tri = array<int, 3>;
using Duo = pair<int, int>;

constexpr tuple<int, int, int> as_tuple(const Tri &t) {
    return {t[0], t[1], t[2]};
}

enum class ZDir { PX, NX, PY, NY, PZ, NZ };
enum class XYRot { D0, D90, D180, D270 };

struct Transform final {
    ZDir z;
    XYRot xy;
};

Duo apply_rotation(const XYRot &r, const Duo xy) {
    const auto [x, y] = xy;

    switch (r) {
    case XYRot::D0:
        return xy;
    case XYRot::D90:
        return {-y, x};
    case XYRot::D180:
        return {-x, -y};
    case XYRot::D270:
        return {y, -x};
    default:
        assert(false && "Impossible rotation");
        return {};
    }
}

Tri apply_transformation(const Transform t, const Tri &p) {
    const auto [x, y, z] = as_tuple(p);

    switch (t.z) {
    case ZDir::PX:
    case ZDir::NX:
    case ZDir::PY:
    case ZDir::NY:
    case ZDir::PZ:
    case ZDir::NZ:
    default:
        assert(false && "Impossible orientation of z-axis");
        return {};
    }
}

bool is_scanner_sep_line(const string &line) {
    return line.find("--- scanner ") == 0;
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

int main() {
    vector<vector<Tri>> data;
    vector<Tri> curr;

    for (string line; getline(cin, line);) {
        if (line.empty()) continue;
        if (is_scanner_sep_line(line)) {
            if (curr.empty()) continue;
            data.push_back(curr);
            curr.clear();
            continue;
        }

        const auto xs = split(",", line);
        Tri t;
        transform(cbegin(xs), cend(xs), begin(t),
                  [](const auto &x) { return stoi(x); });
        curr.push_back(t);
    }

    assert(!curr.empty());
    data.push_back(curr);

    return 0;
}
