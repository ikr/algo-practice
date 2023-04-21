#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using MatQuant = pair<string, int>;
using MatReg = map<string, ll>;

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

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

ll min_ore_to_produce_one_fuel(const CookBook &cook_book) {
    const auto only_ore_required = [&](const string &mat) -> bool {
        const auto &mqs = cook_book.material_inputs.at(mat);
        return sz(mqs) == 1 && mqs[0].first == "ORE";
    };

    const auto ore_num = [&](const auto self, map<string, ll> &mat_reg,
                             const string &mat, const ll times) -> ll {
        assert(mat != "ORE");
        if (only_ore_required(mat)) {
            return times * cook_book.material_inputs.at(mat)[0].second;
        }

        ll result{};

        for (const auto &[submat, submat_q0] :
             cook_book.material_inputs.at(mat)) {
            const auto reused = min(times * submat_q0, mat_reg[submat]);
            const auto submat_q = times * submat_q0 - reused;
            assert(submat_q >= 0);
            mat_reg[submat] -= reused;
            if (!submat_q) continue;

            const auto batch_q =
                cook_book.material_output_quantities.at(submat);

            const auto num_batches = div_ceil(submat_q, 0LL + batch_q);
            const auto additional_ore =
                self(self, mat_reg, submat, num_batches);
            result += additional_ore;

            mat_reg[submat] += batch_q * num_batches - submat_q;
        }

        return result;
    };

    map<string, ll> mat_reg;
    return ore_num(ore_num, mat_reg, "FUEL", 1);
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
