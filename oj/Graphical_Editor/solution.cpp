#include <bits/stdc++.h>
using namespace std;

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args &&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
}

using Color = char;
static constexpr Color WHITE = 'O';

enum class Code {
    CREATE,
    CLEAR,
    DOT,
    VLINE,
    HLINE,
    RECT,
    FILL,
    SAVE,
    EXIT,
    NOOP
};

struct Cmd {
    explicit Cmd(const Code code_) : code(code_) {}
    Cmd() = delete;
    virtual ~Cmd() {}

    Code code;
};

struct CmdCreate final : public Cmd {
    CmdCreate(const int x_sz_, const int y_sz_)
        : Cmd(Code::CREATE), x_sz(x_sz_), y_sz(y_sz_) {}
    CmdCreate() = delete;

    int x_sz;
    int y_sz;
};

struct CmdDot final : public Cmd {
    CmdDot(const int x_, const int y_, const Color color_)
        : Cmd(Code::DOT), x(x_), y(y_), color(color_) {}
    CmdDot() = delete;

    int x;
    int y;
    Color color;
};

struct CmdVLine final : public Cmd {
    CmdVLine(const int x_, const int y1_, const int y2_, const Color color_)
        : Cmd(Code::VLINE), x(x_), y1(min(y1_, y2)), y2(max(y1_, y2_)),
          color(color_) {}
    CmdVLine() = delete;

    int x;
    int y1;
    int y2;
    Color color;
};

struct CmdHLine final : public Cmd {
    CmdHLine(const int x1_, const int x2_, const int y_, const Color color_)
        : Cmd(Code::HLINE), x1(min(x1_, x2_)), x2(max(x1_, x2_)), y(y_),
          color(color_) {}
    CmdHLine() = delete;

    int x1;
    int x2;
    int y;
    Color color;
};

struct CmdRect final : public Cmd {
    CmdRect(const int x1_, const int y1_, const int x2_, const int y2_,
            const Color color_)
        : Cmd(Code::RECT), x1(x1_), y1(y1_), x2(x2_), y2(y2_), color(color_) {
        assert(x1 <= x2);
        assert(y1 <= y2);
    }
    CmdRect() = delete;

    int x1;
    int y1;
    int x2;
    int y2;
    Color color;
};

struct CmdFill final : public Cmd {
    CmdFill(const int x_, const int y_, const Color color_)
        : Cmd(Code::FILL), x(x_), y(y_), color(color_) {}
    CmdFill() = delete;

    int x;
    int y;
    Color color;
};

struct CmdSave final : public Cmd {
    explicit CmdSave(const string &name_) : Cmd(Code::SAVE), name(name_) {}
    CmdSave() = delete;
    string name;
};

vector<string> split(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(begin(s), end(s), delim, -1),
                          sregex_token_iterator{});
}

Code parse_command(const char literal) {
    static const map<char, Code> codes_by_literal{
        {'I', Code::CREATE}, {'C', Code::CLEAR}, {'L', Code::DOT},
        {'V', Code::VLINE},  {'H', Code::HLINE}, {'K', Code::RECT},
        {'F', Code::FILL},   {'S', Code::SAVE},  {'X', Code::EXIT}};

    return codes_by_literal.count(literal) ? codes_by_literal.at(literal)
                                           : Code::NOOP;
}

unique_ptr<Cmd> parse_line(const string &line) {
    const auto terms = split(regex{" "}, line);
    const auto code = parse_command(terms[0][0]);

    switch (code) {
    case Code::CREATE:
        return make_unique<CmdCreate>(stoi(terms[1]), stoi(terms[2]));
    case Code::DOT:
        return make_unique<CmdDot>(stoi(terms[1]) - 1, stoi(terms[2]) - 1,
                                   terms[3][0]);
    case Code::VLINE:
        return make_unique<CmdVLine>(stoi(terms[1]) - 1, stoi(terms[2]) - 1,
                                     stoi(terms[3]) - 1, terms[4][0]);
    case Code::HLINE:
        return make_unique<CmdHLine>(stoi(terms[1]) - 1, stoi(terms[2]) - 1,
                                     stoi(terms[3]) - 1, terms[4][0]);
    case Code::RECT:
        return make_unique<CmdRect>(stoi(terms[1]) - 1, stoi(terms[2]) - 1,
                                    stoi(terms[3]) - 1, stoi(terms[4]) - 1,
                                    terms[5][0]);
    case Code::FILL:
        return make_unique<CmdFill>(stoi(terms[1]) - 1, stoi(terms[2]) - 1,
                                    terms[3][0]);
    case Code::SAVE:
        return make_unique<CmdSave>(terms[1]);
    default:
        return make_unique<Cmd>(code);
    }
}

void handle_create(vector<string> &raster, const CmdCreate &create) {
    raster = vector<string>(create.y_sz, string(create.x_sz, WHITE));
}

void handle_clear(vector<string> &raster) {
    for (auto &row : raster) fill(begin(row), end(row), WHITE);
}

void handle_dot(vector<string> &raster, const CmdDot &dot) {
    raster[dot.y][dot.x] = dot.color;
}

void handle_vline(vector<string> &raster, const CmdVLine &vline) {
    for (auto i = vline.y1; i <= vline.y2; ++i) {
        raster[i][vline.x] = vline.color;
    }
}

void handle_hline(vector<string> &raster, const CmdHLine &hline) {
    for (auto i = hline.x1; i <= hline.x2; ++i) {
        raster[hline.y][i] = hline.color;
    }
}

int main() {
    vector<string> raster;
    for (string line; getline(cin, line);) {
        const auto cmd = parse_line(line);

        switch (cmd->code) {
        case Code::CREATE:
            handle_create(raster, dynamic_cast<const CmdCreate &>(*cmd));
            break;

        case Code::CLEAR:
            handle_clear(raster);
            break;

        case Code::DOT:
            handle_dot(raster, dynamic_cast<const CmdDot &>(*cmd));
            break;

        case Code::VLINE:
            handle_vline(raster, dynamic_cast<const CmdVLine &>(*cmd));
            break;

        case Code::HLINE:
            handle_hline(raster, dynamic_cast<const CmdHLine &>(*cmd));
            break;

        case Code::RECT:
            break;

        case Code::FILL:
            break;

        case Code::SAVE:
            break;

        case Code::NOOP:
            break;

        case Code::EXIT:
            return 0;
        }
    }
    return 0;
}
