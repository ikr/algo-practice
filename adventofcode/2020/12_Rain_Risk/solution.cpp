#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> &lhs, const pair<T, T> &rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

constexpr pi scale(const pi d, const int factor) {
    const auto [dx, dy] = d;
    return {dx * factor, dy * factor};
}

constexpr pair<pi, pi> rotation_matrix_counter_clockwise(const int degrees) {
    switch (degrees) {
    case 90:
        return {{0, -1}, {1, 0}};

    case 180:
        return {{-1, 0}, {0, -1}};

    case 270:
        return {{0, 1}, {-1, 0}};

    default:
        assert(false && "/o\\");
        return {};
    }
}

constexpr pair<pi, pi> rotation_matrix_clockwise(const int degrees) {
    switch (degrees) {
    case 90:
        return rotation_matrix_counter_clockwise(270);

    case 180:
        return rotation_matrix_counter_clockwise(180);

    case 270:
        return rotation_matrix_counter_clockwise(90);

    default:
        assert(false && "/o\\");
        return {};
    }
}

constexpr pi rotate(const pair<pi, pi> &rotation_matrix, const pi v) {
    const auto [vx, vy] = v;
    const auto [ab, cd] = rotation_matrix;
    return {ab.first * vx + ab.second * vy, cd.first * vx + cd.second * vy};
}

int main() {
    pi pos{0, 0};
    pi dir{10, 1};

    for (string line; getline(cin, line);) {
        const char instr_code = line[0];
        const int arg = stoi(line.substr(1));

        switch (instr_code) {
        case 'N':
            dir = dir + pi{0, arg};
            break;

        case 'S':
            dir = dir + pi{0, -arg};
            break;

        case 'E':
            dir = dir + pi{arg, 0};
            break;

        case 'W':
            dir = dir + pi{-arg, 0};
            break;

        case 'F':
            pos = pos + scale(dir, arg);
            break;

        case 'L':
            dir = rotate(rotation_matrix_counter_clockwise(arg), dir);
            break;

        case 'R':
            dir = rotate(rotation_matrix_clockwise(arg), dir);
            break;

        default:
            assert(false && "/o\\");
        }
    }

    const int ans = abs(pos.first) + abs(pos.second);
    cout << ans << '\n';
    return 0;
}
