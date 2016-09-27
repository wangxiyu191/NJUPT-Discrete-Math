#include <cmath>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>
using std::set;
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

bool cToB(char input)
{
    return input == '1';
}
char bToC(bool input)
{
    return input ? 1 : 0;
}
string bToS(bool input)
{
    return input ? "1" : "0";
}

int strReplace(string& str, const string& src, const string& dest)
{
    int counter = 0;
    string::size_type pos = 0;
    while ((pos = str.find(src, pos)) != string::npos) {
        str.replace(pos, src.size(), dest);
        ++counter;
        pos += dest.size();
    }
    return counter;
}

string inffixToSuffix(string input)
{
    std::stack<char> s;
    string output = "";
    for (string::iterator c = input.begin(); c != input.end(); ++c) {
        switch (*c) {
        case '1':
        case '0':
            output += *c;
            break;
        case '(':
            s.push(*c);
            break;
        case ')':
            while (!s.empty()) {
                if (s.top() == '(') {
                    s.pop();
                    break;
                }
                output += s.top();
                s.pop();
            }
            break;
        case '!':
            s.push(*c);
            break;
        case '|':
        case '&':
            while (!s.empty() && s.top() != '(' && s.top() != '>' && s.top() != '=') {
                output += s.top();
                s.pop();
            }
            s.push(*c);
            break;
        case '>':
        case '=':
            while (!s.empty() && s.top() != '(') {
                output += s.top();
                s.pop();
            }
            s.push(*c);
            break;
        }
    }
    while (!s.empty()) {
        output += s.top();
        s.pop();
    }
    return output;
}

bool calcSuffixExpr(string input)
{
    std::stack<bool> s;
    for (string::iterator c = input.begin(); c != input.end(); ++c) {
        if (*c == '0' || *c == '1') {
            s.push(cToB(*c));
        } else if (*c == '!') {
            bool x = s.top();
            s.pop();
            s.push(!x);
        } else {
            bool x = s.top();
            s.pop();
            bool y = s.top();
            s.pop();
            bool result;
            switch (*c) {
            case '|':
                result = x | y;
                break;
            case '&':
                result = x & y;
                break;
            case '>':
                result = (!x) | y;
                break;
            case '=':
                result = (x == y);
                break;
            }
            s.push(result);
        }
    }
    return s.top();
}

void parseInput(string input, vector<string>& output)
{
    string now;
    string symbols = "!()&|=>";
    set<string> outputSet;
    for (string::iterator c = input.begin(); c != input.end(); ++c) {
        if (symbols.find(*c) == string::npos) {
            now += *c;
        } else {
            if (now.length() != 0) {
                outputSet.insert(now);
                now = "";
            }
        }
    }
    if (now.length() != 0) {
        outputSet.insert(now);
        now = "";
    }
    for (set<string>::iterator str = outputSet.begin(); str != outputSet.end(); ++str) {
        output.push_back(*str);
    }
}

int main()
{
    cout << "请使用 ! | & > =" << endl;
    cout << "hello,using ! | & > = please" << endl;
    string input;
    cin >> input;
    vector<string> varName;
    parseInput(input, varName);
    int varNum = varName.size();
    int tableNum = (int)pow(2, varNum);
    bool table[tableNum][varNum + 1];

    for (int i = 0; i < tableNum; i++) {
        int num = i;
        for (int j = 0; j < varNum; j++) {
            table[i][j] = num % 2;
            num /= 2;
        }
    }
    cout << "真值表" << endl;
    cout << "Truth table" << endl;
    for (int i = 0; i < varNum; i++) {
        cout << varName[i] << '\t';
    }
    cout << input << endl;
    for (int i = 0; i < varNum + 1; i++) {
        cout << "-\t";
    }
    cout << endl;
    for (int i = 0; i < tableNum; i++) {
        string expr = input;
        for (int j = 0; j < varNum; j++) {
            strReplace(expr, varName[j], bToS(table[i][j]));
            cout << bToS(table[i][j]) << "\t";
        }
        string suffixExpr = inffixToSuffix(expr);
        table[i][varNum] = calcSuffixExpr(suffixExpr);
        cout << table[i][varNum] << endl;
    }

    cout << "主合取范式" << endl;
    cout << "Principal Conjunctive Normal Form" << endl;
    bool first = true;
    for (int i = 0; i < tableNum; i++) {
        if (table[i][varNum]) {
            continue;
        }
        if (first) {
            first = false;
        } else {
            cout << "&";
        }
        cout << "(";
        for (int j = 0; j < varNum; j++) {
            if (table[i][j]) {
                cout << "!";
            }
            cout << varName[j];
            if (j != varNum - 1) {
                cout << "|";
            }
        }
        cout << ")";
    }
    cout << endl;

    cout << "主析取范式" << endl;
    cout << "Principal Disjunctive Normal Form" << endl;
    first = true;
    for (int i = 0; i < tableNum; i++) {
        if (table[i][varNum] == false) {
            continue;
        }
        if (first) {
            first = false;
        } else {
            cout << "|";
        }
        cout << "(";
        for (int j = 0; j < varNum; j++) {
            if (table[i][j] == false) {
                cout << "!";
            }
            cout << varName[j];
            if (j != varNum - 1) {
                cout << "&";
            }
        }
        cout << ")";
    }
    cout << endl;

    return 0;
}