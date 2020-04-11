#include <bits/stdc++.h>

using namespace std;

double falling_duration(const double G, const double h0) {
    return sqrt(2.0 * h0 / G);
}

double falling_position(const double G, const double h0, const double dt) {
    return G * dt * dt / 2.0;
}

double rebound_velocity(const double v, const double energy_lost_percent) {
    return sqrt(v * v * (1.0 - energy_lost_percent / 100.0))
}

double rebound_duration(const double G, const double v) {
    return v / G;
}

double rebound_position(const double G, const double v, const double dt) {
	return (v * dt) - (G * dt * dt) / 2.0;
}

struct BouncingBall final {
     double getPosition(int g, int h, int p, int t) const {
         const double G = g / 100.0;
     }
};
