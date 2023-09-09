#include <bits/stdc++.h>
using namespace std;

static const map<string, int> P{{"tourist", 3858},   {"ksun48", 3679},
                                {"Benq", 3658},      {"Um_nik", 3648},
                                {"apiad", 3638},     {"Stonefeang", 3630},
                                {"ecnerwala", 3613}, {"mnbvmar", 3555},
                                {"newbiedmy", 3516}, {"semiexp", 3481}};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string x;
    cin >> x;

    cout << P.at(x) << '\n';
    return 0;
}
