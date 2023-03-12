#include <bits/stdc++.h>
using namespace std;

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

int min_ore_to_produce_one_fuel(const CookBook &cook_book) {
    const auto only_ore_required = [&](const string &mat) -> bool {
        assert(cook_book.material_inputs.contains(mat));
        const auto &mqs = cook_book.material_inputs.at(mat);
        return sz(mqs) == 1 && mqs[0].first == "ORE";
    };

    const auto ore_num = [&](const auto self, map<string, int> &mat_reg,
                             const string &mat) -> int {
        assert(mat != "ORE");

        if (only_ore_required(mat)) {
            const auto req_ore_total =
                cook_book.material_inputs.at(mat)[0].second;

            const auto ore_av = mat_reg["ORE"];
            const auto ore_recycled = min(req_ore_total, ore_av);
            mat_reg["ORE"] -= ore_recycled;

            assert(cook_book.material_output_quantities.contains(mat));
            mat_reg[mat] += cook_book.material_output_quantities.at(mat);
            return req_ore_total - ore_recycled;
        }

        for (const auto &[submat, submat_q] :
             cook_book.material_inputs.at(mat)) {
            assert(cook_book.material_output_quantities.contains(submat));
            const auto batch_q =
                cook_book.material_output_quantities.at(submat);

            const auto num_batches = div_ceil(submat_q, batch_q);
        }
    };

    map<string, int> mat_reg;
    return ore_num(ore_num, mat_reg, "FUEL");
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

    cout << min_ore_to_produce_one_fuel(
                {material_output_quantities, material_inputs})
         << '\n';
    return 0;
}
