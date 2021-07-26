#include <bits/stdc++.h>

using namespace std;

static const double EPSILON = 0.000000001;

double falling_duration(const double G, const double h0) {
    return sqrt(2.0 * h0 / G);
}

double falling_position(const double G, const double h0, const double dt) {
    return h0 - G * dt * dt / 2.0;
}

double rebound_velocity(const double v, const double energy_lost_percent) {
    return sqrt(v * v * (1.0 - energy_lost_percent / 100.0));
}

double rebound_duration(const double G, const double v) {
    return v / G;
}

double rebound_position(const double G, const double v, const double dt) {
	return (v * dt) - (G * dt * dt) / 2.0;
}

struct BouncingBall final {
     double getPosition(const int g, const int h, const int p, const int t) const {
         const double G = g / 100.0;
         double T = t;
         double y = h;
         double v = 0.0;
         bool rebounding = false;

        while (abs(T) > EPSILON) {
            const double next_stage_duration = 
                rebounding ? rebound_duration(G, v) : falling_duration(G, y);

            if (T <= next_stage_duration) {
                y = rebounding ? rebound_position(G, v, T) : falling_position(G, y, T);
                break;
            }

            if (rebounding) {
                const double dt = rebound_duration(G, v);
                T -= dt;
                y = rebound_position(G, v, dt);
                v = 0.0;
            } else {
                const double dt = falling_duration(G, y);
                T -= dt;
                v = rebound_velocity(G * dt, p);
                y = 0.0;
            }

            rebounding = !rebounding;
        }

         return y;
     }
};
