#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include <map>
#include <cmath>

std::map<std::string, double> variables;

// Token stuff
struct token {
    char kind;
    double value;

    token(char ch) : kind(ch), value(0) {}
    token(char ch, double val) : kind(ch), value(val) {}
};

class token_stream {
    bool full;
    token buffer;

public:
    token_stream() : full(false), buffer(0) {}

    token get();
    void putback(token t);
    void ignore(char c);
};

void token_stream::putback(token t) {
    if (full) throw std::runtime_error("putback() into a full buffer");
    buffer = t;
    full = true;
}

token token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }

    char ch;
    std::cin >> ch;

    if (isalpha(ch)) {
        std::string s;
        s += ch;
        while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
        std::cin.putback(ch);
        if (s == "pi") return token('c', 3.141592653589793238462643383);
        if (s == "q") return token('q'); // Handle quit command
        throw std::runtime_error("Unknown variable: " + s);
    }

    switch (ch) {
        case ';':
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case 'q':  // Directly handle 'q' if not part of an identifier
            return token(ch);
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            {
                std::cin.putback(ch);
                double val;
                std::cin >> val;
                return token('8', val);
            }
        default:
            throw std::runtime_error("Bad token");
    }
}



void token_stream::ignore(char c) {
    // first look in buffer:
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // now search input:
    char ch = 0;
    while (std::cin >> ch)
        if (ch == c) return;
}

token_stream ts;

double expression();

double primary() {
    token t = ts.get();
    switch (t.kind) {
        case 'c': // Handle constant
            return t.value;
        case '(':
            {
                double d = expression();
                t = ts.get();
                if (t.kind != ')') throw std::runtime_error("')' expected");
                return d;
            }
        case '8':
            return t.value;
        case '-':
            return -primary();
        default:
            throw std::runtime_error("Primary expected");
    }
}



double term() {
    double left = primary();
    while (true) {
        token t = ts.get();
        switch (t.kind) {
            case '*':
                left *= primary();
                break;
            case '/':
                {
                    double d = primary();
                    if (d == 0) throw std::runtime_error("Divide by zero");
                    left /= d;
                    break;
                }
            case '%':
                {
                    double d = primary();
                    if (d == 0) throw std::runtime_error("Divide by zero");
                    left = fmod(left, d);  // Use fmod for floating-point modulus
                    break;
                }
            default:
                ts.putback(t);
                return left;
        }
    }
}


double expression() {
    double left = term();
    while (true) {
        token t = ts.get();
        switch (t.kind) {
            case '+':
                left += term();
                break;
            case '-':
                left -= term();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

void clean_up_mess() {
    ts.ignore(';');
}

void calculate() {
    while (std::cin)
        try {
            std::cout << "Enter expression (add ; to end, q to quit): ";
            token t = ts.get();
            while (t.kind == ';') t = ts.get(); // 'eat' semicolons
            if (t.kind == 'q') return;
            ts.putback(t);
            std::cout << "Result: " << expression() << std::endl;
        }
        catch (std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            clean_up_mess();
        }
}

int main() {
    try {
        calculate();
        return 0;
    }
    catch (...) {
        std::cerr << "Unknown exception!\n";
        return 2;
    }
}
