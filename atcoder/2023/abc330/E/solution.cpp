#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, Q;
    cin >> N >> Q;

    vector<int> F(N + 1, 0);
    vector<int> A(N);

    for (auto &a : A) {
        cin >> a;
        if (a <= N) ++F[a];
    }

    set<int> holes;
    for (int i = 0; i <= N; ++i) {
        if (!F[i]) holes.insert(i);
    }

    const auto mutate = [&](const int i, const int x) -> void {
        if (const auto x0 = A[i]; x0 <= N) {
            assert(F[x0] > 0);
            --F[x0];
            if (F[x0] == 0) holes.insert(x0);
        }

        if (x <= N) {
            holes.erase(x);
            ++F[x];
        }

        A[i] = x;
    };

    for (int k = 1; k <= Q; ++k) {
        int ik, xk;
        cin >> ik >> xk;
        --ik;

        mutate(ik, xk);
        assert(!empty(holes));
        cout << *cbegin(holes) << '\n';
    }

    return 0;
}
