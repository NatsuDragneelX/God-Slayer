#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include <map>
#include <cmath>

std::map<std::string, double> variables;

// Initialize variables with constants
void init_variables() {
    variables["pi"] = 3.1415926535897932385;
    variables["e"] = 2.7182818284590452354;
    variables["phi"] = 1.61803398874989484820;
    variables["tau"] = 6.2831853071795864769;
    variables["isqrd"] = -1;
    variables["sqrt2"] = 1.4142135623;
    variables["sqrt3"] = 1.7320508075;
    variables["fibonacci"] = 3.359885666243178;
}

struct token {
    char kind;
    double value;
    std::string name;

    token(char ch) : kind(ch), value(0) {}
    token(char ch, double val) : kind(ch), value(val) {}
    token(char ch, std::string n) : kind(ch), name(n) {}
};

class token_stream {
    bool full;
    token buffer;
public:
    token_stream() : full(false), buffer(0) {}

    token get();
    void putback(token t) {
        if (full) throw std::runtime_error("putback() into a full buffer");
        buffer = t;
        full = true;
    }
    void ignore(char c);
};

token token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }
    char ch;
    std::cin >> std::ws >> ch;

    switch (ch) {
        case ';': case '(': case ')': case '+': case '-':
        case '*': case '/': case '%': case '=':
        case 'q': return token(ch);
        default:
            if (isdigit(ch) || ch == '.') {
                std::cin.putback(ch);
                double val;
                std::cin >> val;
                return token('8', val);
            } else if (isalpha(ch)) {
                std::string s;
                s += ch;
                while (std::cin.get(ch) && (isalnum(ch) || ch == '_')) s += ch;
                std::cin.putback(ch);
                if (variables.count(s)) return token('a', s); // Return a variable token
                return token('a', s); // Or potentially a function or new variable
            }
            throw std::runtime_error("Bad token");
    }
}

void token_stream::ignore(char c) {
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    char ch;
    while (std::cin >> ch)
        if (ch == c) return;
}

token_stream ts;

double expression();

double primary() {
    token t = ts.get();
    switch (t.kind) {
        case '8': return t.value;
        case 'a': {
            std::string var_name = t.name;
            token next_token = ts.get();
            if (next_token.kind == '=') {
                double value = expression();
                variables[var_name] = value; // Assign a new value to the variable
                return value;
            } else {
                ts.putback(next_token);
                if (variables.find(var_name) == variables.end())
                    throw std::runtime_error("Undefined variable: " + var_name);
                return variables[var_name]; // Retrieve the variable's value
            }
        }

        case '(':
            {
                double d = expression();
                t = ts.get();
                if (t.kind != ')') throw std::runtime_error("')' expected");
                return d;
            }
        case '-':
            return -primary();

        case 'f':  // Handling function calls
            if (t.name == "sqrt") {
                double d = primary();
                if (d < 0) throw std::runtime_error("Square root of negative number");
                return std::sqrt(d);
            } else if (t.name == "exp") {
                double d = primary();
                return std::exp(d);
            } else if (t.name == "log") {
                double d = primary();
                if (d <= 0) throw std::runtime_error("Logarithm of non-positive number");
                return std::log(d);
            }
            throw std::runtime_error("Unsupported function: " + t.name);
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
                    left = fmod(left, d);
                    break;
                }

            case '^':
                {
                    double exponent = primary();
                    left = std::pow(left, exponent);
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
    init_variables(); // Initialize constants and variables

    while (true) {
        try {
            std::cout << "Enter expression (add ; to end, q to quit): ";
            token t = ts.get();
            while (t.kind == ';') t = ts.get(); // Ignore semicolons
            if (t.kind == 'q') return;
            ts.putback(t);
            std::cout << "Result: " << expression() << std::endl;
        }
        catch (std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            clean_up_mess();
        }
    }
}


int main() {
    init_variables();
    try {
        calculate();
    } catch (...) {
        std::cerr << "Unknown exception!\n";
        return 2;
    }
    return 0;
}