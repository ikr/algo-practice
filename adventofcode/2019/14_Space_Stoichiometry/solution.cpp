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

using MatQuant = pair<string, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

MatQuant parse_material_quantity(const string &src) {
    const auto parts = split(" ", src);
    return {parts[1], stoi(parts[0])};
}

vector<MatQuant> parse_material_quantities(const string &src) {
    const auto parts = split(", ", src);
    vector<MatQuant> result(sz(parts));
    transform(cbegin(parts), cend(parts), begin(result),
              parse_material_quantity);
    return result;
}

struct CookBook final {
    map<string, int> material_output_quantities;
    map<string, vector<MatQuant>> material_inputs;
};

map<string, int> to_material_registry(const vector<MatQuant> &src) {
    map<string, int> result;
    for (const auto &[k, v] : src) result[k] += v;
    return result;
}

vector<MatQuant> to_material_quantities(const map<string, int> &reg) {
    vector<MatQuant> result(sz(reg));
    transform(cbegin(reg), cend(reg), begin(result),
              [](const auto &a) { return a; });
    return result;
}

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

vector<MatQuant> reduce_once(const CookBook &cook_book,
                             const vector<MatQuant> &src) {
    const auto &[qs, ins] = cook_book;
    const auto reg = to_material_registry(src);
    map<string, int> reg_;

    for (const auto &[k, v] : reg) {
        if (k == "ORE") {
            reg_[k] += v;
            continue;
        }

        const auto cycles = div_ceil(v, qs.at(k));

        for (const auto &[mat, quant] : ins.at(k)) {
            reg_[mat] += cycles * quant;
        }
    }

    return to_material_quantities(reg_);
}

int main() {
    map<string, int> material_output_quantities;
    map<string, vector<MatQuant>> material_inputs;

    for (string line; getline(cin, line);) {
        const auto parts = split(" => ", line);
        const auto input = parse_material_quantities(parts[0]);
        const auto output = parse_material_quantity(parts[1]);

        if (output.first == "FUEL") assert(output.second == 1);
        assert(!material_output_quantities.contains(output.first));
        material_output_quantities.emplace(output.first, output.second);
        material_inputs.emplace(output.first, input);
    }

    const CookBook cook_book{material_output_quantities, material_inputs};
    vector<MatQuant> mat_quants{{"FUEL", 1}};

    for (;;) {
        mat_quants = reduce_once(cook_book, mat_quants);
        cerr << mat_quants << endl;
        if (sz(mat_quants) == 1) break;
    }

    cout << mat_quants << endl;
    return 0;
}
