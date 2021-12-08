#include <bits/stdc++.h>
#include "C:/CP/Debug.h"
using namespace std;

#define int long long
#define endl '\n'
#define sz(a) (int)((a).size())
#define all(a) (a).begin(),(a).end()
#define allr(a) (a).rbegin(),(a).rend()

typedef long double lld;

const double pi = 3.141592653589793;
const double epsilon  = 0.0000000001;

template<typename T>void print(T t) { cout << t; }
template<typename T, typename... Args>void print(T t, Args... args) { cout << t << " "; print(args...); }
template<typename... Args>void printl(Args... args) { print(args...); cout << endl; }

const int maxn = 1<<22 + 1;
string command, buffer;
int ans;

set<string> preUnOp = {"-", "~"};
set<string> postUnOp = {"!", "$"};
set<string> binOp = {"+", "-", "*", "/", "//", "%", "**", "c", "p", "|", "&", "^", "@", ":"};
string compute(string a, string b, string op);
int precedence(string op);

#include "basicTools.h"
#include "commandTools.h"

int compute(int a, int b, string op) //Operators which will always return an integer
{
    if (op=="%") return a%b;

    if (op==":") return gcd(a,b);

    if (op=="!") return fact(a); 
    
    if (op=="$") return stoll(to_string(a), 0, 2); // TODO: checkBinary(a);

    if (op=="c") return ncr(a, b);
    if (op=="p") return npr(a, b);

    if (op=="|") return a|b;
    if (op=="&") return a&b;
    if (op=="^") return a^b;
    if (op=="~") return ~b;

    return 0;
}

// double compute(int a, int b, string op) //Operators which will never return an integer
// {

//     if (op=="@") return log(a)/log(b);

//     return 0.0;
// }


string compute(string a, string b, string op)
{
    if (op=="+") return to_string((stoll(a)+stoll(b))%modl());
    if (op=="-") return a-b;
    if (op=="*") return mulmod(a, b, modl());
    if (op=="//") return a/b;
    if (op=="**") return power(a, b, modl());

    // if (op=="+") return a+b;
    // if (op=="-") return a-b;
    // if (op=="*") return a*b;
    if (op=="/") return a/b;
    if (op=="**") return pow(a, b);
    return "";
}

int precedence(string op)
{
    if(op == ":") return 5;
    if(op == "&"||op == "^"||op == "|") return 10;
    if(op == "+") return 20;
    if(op == "*"||op == "/"||op == "%"||op == "//") return 30;
    if(op == "**"||op == "@"||op == "c"||op == "p") return 40;
    if(op == "~" || op == "-") return 50;
    if(op == "!" || op == "$") return 100;
    return 0;
}

bool solve(string& command)
{
    vector<string> tokenList = splitCommand(command); // Splits digits, brackets & rest.

    if (!splitOperator(tokenList)) return 0; // Split rest into valid operators or report.
    if (!HandleMinus(tokenList)) return 0; // Convert binary '-' to unary '-'.
    if (!UnToBin(tokenList)) return 0; // Convert unary operators as pseudo binary.
    if (!checkBrackets(tokenList)) return 0; // Check order of brackets or report. 

    debug(tokenList);
    
    command = evaluate(tokenList);
    printl(command);
    return 1;
}

signed main()
{
    loadfiles();    
    cout << setprecision(10) << fixed;   
    while (1)
    {
        buffer = "";
        getline(cin, command);
        for (auto& e : command) e = tolower(e);
        for (auto& e : command) if(e!=' ') buffer+=e; 
        command = buffer;

        if (command == "exit") break;
        else if (command == "mod") changeMod();
        else if (command == "modl") changeModl();
        else if (command == "help") giveHelp();
        else if (command.back() == '#')
        {
            command.pop_back();
            if (solve(command)) return toBinary(command);
            else giveError();
        }
        else if (!solve(command)) giveError();
    }
}