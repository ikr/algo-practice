#include <bits/stdc++.h>
using namespace std;

// We traverse the graph in the topological order, starting from {"FUEL" 1}, —
// actually, it's a post-order traversal — keeping the inventory of all the
// excess materials. While traversing, we shall also track, how many ORE-s we
// need to add total, in order for all the necessary transitions to succeed. The
// {c q₁} → {c q₂} graph edges have to be treated in a special way. We find the
// smallest integer k such that kq₁ ≥ q₂. Thus, we need to produce the
// left-hand-side material quantity k times, in order to enable the {c q₁} → {c
// q₂} transition. Before telling, how many ORE is required for {c q₂}, we
// already know, how many ORE-s is required to produce the {c q₁}, and, also,
// how many leftovers of different kinds we'd get then. Therefore, we can tell,
// how many ORE-s is optimal for the production of the {c q₂}.

using ll = long long;
using MatQuant = pair<string, int>;
using MatReg = map<string, ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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

MatReg merge(MatReg a, const MatReg &b) {
    for (const auto &[k, v] : b) a[k] += v;
    return a;
}

MatReg scale_by(const ll k, MatReg a) {
    for (auto &[_, v] : a) v *= k;
    return a;
}

ll min_ore_to_produce_one_fuel(const CookBook &cook_book) {
    const auto only_ore_required = [&](const string &mat) -> bool {
        const auto &mqs = cook_book.material_inputs.at(mat);
        return sz(mqs) == 1 && mqs[0].first == "ORE";
    };

    const auto ore_num = [&](const auto self, map<string, ll> &mat_reg,
                             const string &mat) -> ll {
        assert(mat != "ORE");
        if (only_ore_required(mat)) {
            cerr << "Need " << cook_book.material_inputs.at(mat)[0].second
                 << " ORE for " << cook_book.material_output_quantities.at(mat)
                 << ' ' << mat << endl;
            return cook_book.material_inputs.at(mat)[0].second;
        }

        ll result{};

        for (const auto &[submat, submat_q0] :
             cook_book.material_inputs.at(mat)) {
            const auto reused = min(0LL + submat_q0, mat_reg[submat]);
            const auto submat_q = submat_q0 - reused;
            assert(submat_q >= 0);
            mat_reg[submat] -= reused;
            cerr << "Need " << submat_q << ' ' << submat << " for "
                 << cook_book.material_output_quantities.at(mat) << ' ' << mat
                 << ", " << reused << " reused" << endl;
            if (!submat_q) continue;

            const auto batch_q =
                cook_book.material_output_quantities.at(submat);

            const auto num_batches = div_ceil(submat_q, 0LL + batch_q);
            const auto additional_ore =
                num_batches * self(self, mat_reg, submat);
            result += additional_ore;

            cerr << "Ordered " << num_batches << "x got " << additional_ore
                 << " ORE" << endl;
            mat_reg[submat] += batch_q * num_batches - submat_q;
            cerr << "mat_reg: " << mat_reg << endl;
        }

        cerr << "Need " << result << " ORE to produce "
             << cook_book.material_output_quantities.at(mat) << ' ' << mat
             << endl;
        return result;
    };

    map<string, ll> mat_reg;
    const auto result = ore_num(ore_num, mat_reg, "FUEL");
    cerr << "Final mat_reg: " << mat_reg << endl;
    return result;
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
