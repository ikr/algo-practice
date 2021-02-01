#include <bits/stdc++.h>
using namespace std;
using RoCo = pair<int, int>;

enum class HorzSeg { T, M, B };
enum class VertSeg { LT, LB, RT, RB };

constexpr RoCo glyph_dimensions(const int s) { return {2 * s + 3, s + 2}; }

RoCo screen_dimentions(const int s, const int num_glyphs) {
    assert(num_glyphs > 0);
    const auto gd = glyph_dimensions(s);
    return {gd.first, gd.second * num_glyphs + num_glyphs - 1};
}

int co_of_glyph(const int s, const int glyph_index) {
    const auto gd = glyph_dimensions(s);
    return (gd.second + 1) * glyph_index;
}

void render_horz_seg(vector<string> &glyph, const HorzSeg kind) {
    const int h = glyph.size();
    assert(h > 0);
    const int w = glyph[0].size();

    const int ro = [kind, h]() -> int {
        switch (kind) {
        case HorzSeg::T:
            return 0;
        case HorzSeg::M:
            return h / 2;
        default:
            assert(kind == HorzSeg::B);
            return h - 1;
        }
    }();

    for (int co = 1; co < w - 1; ++co) {
        glyph[ro][co] = '-';
    }
}

void render_vert_seg(vector<string> &glyph, const VertSeg kind) {
    const int h = glyph.size();
    assert(h > 3);
    const int seg_length = (h - 3) / 2;

    const RoCo start = [kind, seg_length]() -> RoCo {
        switch (kind) {
        case VertSeg::LT:
            return {1, 0};
        case VertSeg::LB:
            return {seg_length + 2, 0};
        case VertSeg::RT:
            return {1, seg_length + 1};
        default:
            assert(kind == VertSeg::RB);
            return {seg_length + 2, seg_length + 1};
        }
    }();

    for (int d = 0; d < seg_length; ++d) {
        glyph[start.first + d][start.second] = '|';
    }
}

vector<string> empty_glyph(const int s) {
    const auto d = glyph_dimensions(s);
    return vector<string>(d.first, string(d.second, ' '));
}

void bitblt(vector<string> &display, const vector<string> &glyph,
            const int co) {
    const int h = glyph.size();
    assert(h > 0);
    const int w = glyph[0].size();

    for (int ro = 0; ro < h; ++ro) {
        display[ro].replace(co, w, glyph[ro]);
    }
}

void render_digit(vector<string> &glyph, const char digit) {
    const int x = digit - '0';
    assert(0 <= x && x <= 9);

    const vector<HorzSeg> all_horz{HorzSeg::T, HorzSeg::M, HorzSeg::B};

    const array<vector<HorzSeg>, 10> horz_segs{
        vector<HorzSeg>{HorzSeg::T, HorzSeg::B}, // 0
        {},                                      // 1
        all_horz,                                // 2
        all_horz,                                // 3
        vector<HorzSeg>{HorzSeg::M},             // 4
        all_horz,                                // 5
        all_horz,                                // 6
        vector<HorzSeg>{HorzSeg::T},             // 7
        all_horz,                                // 8
        all_horz                                 // 9
    };

    const array<vector<VertSeg>, 10> vert_segs{
        vector<VertSeg>{VertSeg::LT, VertSeg::LB, VertSeg::RT,
                        VertSeg::RB},                           // 0
        vector<VertSeg>{VertSeg::RT, VertSeg::RB},              // 1
        vector<VertSeg>{VertSeg::RT, VertSeg::LB},              // 2
        vector<VertSeg>{VertSeg::RT, VertSeg::RB},              // 3
        vector<VertSeg>{VertSeg::LT, VertSeg::RT, VertSeg::RB}, // 4
        vector<VertSeg>{VertSeg::LT, VertSeg::RB},              // 5
        vector<VertSeg>{VertSeg::LT, VertSeg::LB, VertSeg::RB}, // 6
        vector<VertSeg>{VertSeg::RT, VertSeg::RB},              // 7
        vector<VertSeg>{VertSeg::LT, VertSeg::LB, VertSeg::RT,
                        VertSeg::RB},                          // 8
        vector<VertSeg>{VertSeg::LT, VertSeg::RT, VertSeg::RB} // 9
    };

    for (const auto seg : horz_segs[x]) render_horz_seg(glyph, seg);
    for (const auto seg : vert_segs[x]) render_vert_seg(glyph, seg);
}

vector<string> display_n(const int s, const string n) {
    const auto screen_dim = screen_dimentions(s, n.size());
    vector<string> screen(screen_dim.first, string(screen_dim.second, ' '));

    for (auto i = 0U; i < n.size(); ++i) {
        auto g = empty_glyph(s);
        render_digit(g, n[i]);
        bitblt(screen, g, (g[0].size() + 1) * i);
    }

    return screen;
}

int main() {
    for (;;) {
        int s;
        string n;
        cin >> s >> n;
        if (!s) break;

        const auto rows = display_n(s, n);
        for (const auto &row : rows) cout << row << '\n';
        cout << '\n';
    }
    return 0;
}
