#include <iostream>
#include <string>
#include <limits>
#include <numeric>

using namespace std;

class Parser;

class calc {
private:
    int numerator;
    int denominator;
    void less() {
        int d = gcd(numerator, denominator);
        numerator /= d;
        denominator /= d;
    }
public:
    calc(int n, int d) : numerator(n), denominator(d) {
        if (d == 0) throw invalid_argument("determinator cant be 0;");
        less();
    };
    void print() const;
    calc operator + (const calc& other);
    calc operator - (const calc& other);
    calc operator * (const calc& other);
    calc operator | (const auto& other);
};

void calc::print() const{
    if (denominator == 1) cout << numerator;
    else cout << numerator << "/" << denominator;
}

calc calc::operator+(const calc& other) {
    return { numerator * other.denominator + denominator * other.numerator,
            denominator * other.denominator };
}

calc calc::operator-(const calc& other) {
    return { numerator * other.denominator - denominator * other.numerator,
            denominator * other.denominator };
}

calc calc::operator*(const calc& other) {
    return { numerator * other.numerator,
        denominator * other.denominator };
}

calc calc::operator|(const auto& other) {
    return { numerator * other.denominator, 
        denominator * other.numerator };
}


class Parser {
public:
    void parse(const string& input);
    void createfractal(string& s);
    void countingdractal(int leftn, int rightn, int rightd, int leftd, char op);
};

void Parser::parse(const string& input) {
    string s = input;

    s.erase(remove(s.begin(), s.end(), ' '), s.end());

    Parser::createfractal(s);
}

void Parser::createfractal(string& s) {
    int opPos{};
    char op;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '|') {
            opPos = i; op = s[i]; break;
        }
    }

    string left = s.substr(0, opPos);
    string right = s.substr(opPos + 1);

    int slashPos = left.find('/');
    int leftn = stoi(left.substr(0, slashPos));
    int leftd = stoi(left.substr(slashPos + 1));
    slashPos = right.find('/');
    int rightn = stoi(right.substr(0, slashPos));
    int rightd = stoi(right.substr(slashPos + 1));

    Parser::countingdractal(leftn, rightn, rightd, leftd, op);
}

void Parser::countingdractal(int leftn, int rightn, int rightd, int leftd, char op) {
    try {
        calc firstfract(leftn, leftd);
        calc secondfract(rightn, rightd);
        cout << "Результат разбора: ";
        firstfract.print();  // Вызов метода у первого объекта
        cout << " " << op << " ";
        secondfract.print();      // Вызов метода у второго объекта

        calc res(0, 1);
        switch (op) {
        case '+': cout << " = ";  res = firstfract + secondfract; res.print(); break;
        case '-': cout << " = "; res = firstfract - secondfract; res.print(); break;
        case '*': cout << " = "; res = firstfract * secondfract; res.print(); break;
        case '|': cout << " = "; res = firstfract | secondfract; res.print(); break;
        }
    }
    catch (const invalid_argument& e) {
        cerr << "[ERROR]: " << e.what() << endl;
    }
}
