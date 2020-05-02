#include <bits/stdc++.h>

using namespace std;

struct Quad final {
    int a, b, c, d;
};

vector<vector<int>> dist_mx(const int N, const vector<Quad> &qs) {
    vector<vector<int>> ds(N + 1, vector<int>(N + 1, -1));
    
    for (const auto &q : qs) {
        ds[q.a][q.b] = q.c;
    }
    
    return ds;
}

bool is_valid_dist_mx(const vector<vector<int>> &ds) {
    const int sz = ds.size();
    
    for (int i = 1; i < sz - 2; ++i) {
        for (int j = i + 1; j < sz - 1; ++j) {
            for (int k = j + 1; k < sz; ++k) {
                if (ds[i][k] != -1 && ds[i][k] < ds[i][j] + ds[j][k]) return false;
            }
        }
    }
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    int N, M, Q;
    cin >> N >> M >> Q;
    
    vector<Quad> qs(Q, {-1, -1, -1, -1});
    
    for (auto &q : qs) {
        cin >> q.a >> q.b >> q.c >> q.d;
    }

    return 0;
}
