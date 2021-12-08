#pragma once

void giveHelp()
{
	printl("\nexit : Exit from mycalc\n");
    printl("+ : Add (a+b)");
    printl("- : Subtract (a-b)");
    printl("* : Multiply (a*b)");
    printl("** : Power (a**b)");
    printl("/ : Divide (a/b)");
    printl("// : Integral Divide (a//b)");
    printl("% : Modulo (a%b)\n");
    printl(": : GCD (a:b)\n");
    printl("@ : Log(a)base(b) (a@b)\n");
    printl("c : nCr (aCb)");
    printl("p : nPr (aPb)");
    printl("! : Fatorial (a!)\n");
    printl("# : To Binary (a#)");
    printl("$ : To Decimal (a#)\n");
    printl("| : Or (a|b)");
    printl("& : And (a&b)");
    printl("^ : Xor (a^b)");
    printl("~ : Not (~b)\n");
    printl("mod : switch mod between 998244353 and 1000000007");
    printl("modl : change mod to infinity and back.\n");
}

void giveError()
{
	printl("Invalid Input! :(\n Type 'help' to learn more...");
}

vector<string> splitCommand(string& command)
{
    int last=-1;
    vector<string> tokenList;
    tokenList.push_back("(");
    for (auto& c : command)
    {
        if (isdigit(c))
        {
            if (last!=0) tokenList.push_back(""); 
            tokenList.back()+=c;
            last=0;
        }
        else if (c=='(' || c==')')
        {
            tokenList.push_back(string(1, c));
            last=1;
        }
        else
        {
            if (last!=2) tokenList.push_back("");
            tokenList.back()+=c;
            last=2;
        }
    }
    tokenList.push_back(")");
    return tokenList;
}

bool splitOperator(vector<string>& tokens)
{
    vector<string> tokenList;
    for (auto& token : tokens)
    {
        if (isdigit(token[0]) || token == "(" || token == ")") tokenList.push_back(token); 
        else
        {
            buffer = "";
            if (compOp(postUnOp, string(1, token[0]))) 
            {
                tokenList.push_back(string(1, token[0]));
                token = token.substr(1);
            }
            if (token.size())
            {
                if (compOp(preUnOp, string(1, token.back()))) 
                {
                    buffer = string(1, token.back());
                    token.pop_back();
                }
            }
            if (token.size())
            {
                if (compOp(binOp, token)) tokenList.push_back(token);
                else return 0;
            }
            if (buffer.size())
                tokenList.push_back(buffer);

        }
    }
    tokens = tokenList;
    return 1;
}

bool HandleMinus(vector<string>& tokens)
{
    vector<string> tokenList;
    tokenList.push_back(tokens[0]);
    for (int i = 1; i < tokens.size(); ++i)
    {
        if (tokens[i]=="-" && isdigit(tokens[i-1][0])) tokenList.push_back("+");
        if (tokens[i]=="-" && tokens[i-1]=="-") { tokenList.pop_back(); continue; }
        tokenList.push_back(tokens[i]);
    }
    tokens = tokenList;
    return 1;
}

bool UnToBin(vector<string>& tokens)
{
    vector<string> tokenList;
    for (int i = 0; i < tokens.size(); ++i)
    {
        if (compOp(preUnOp, tokens[i]))
            tokenList.push_back("0"), tokenList.push_back(tokens[i]);
        else if (compOp(postUnOp, tokens[i]))
            tokenList.push_back(tokens[i]), tokenList.push_back("0");
        else
            tokenList.push_back(tokens[i]);
    }
    tokens = tokenList;
    return 1;
}

bool checkBrackets(vector<string>& tokens)
{
    int brac = 0;
    if (tokens[0] == "(") brac++; else return 0;

    for (int i = 1; i < tokens.size()-1; ++i)
    {
        if (tokens[i] == "("){
            if (tokens[i-1] == ")" || tokens[i+1] == ")") return 0;
            brac++;
        }
        else if (tokens[i] == ")"){
            if (tokens[i-1] == "(" || tokens[i+1] == "(") return 0;
            brac--;
        }
        else if (isdigit(tokens[i][0])){
            if (tokens[i-1] == ")" || tokens[i+1] == "(") return 0;
        }
        else{
            if (tokens[i-1] == "(" || tokens[i+1] == ")") return 0;            
        }

        if (brac<=0) return 0;
    }
    return 1;
}

bool isValidNumber(string s)
{
    try{ 
        stoll(s);
    }
    catch (exception& e){ 
        return 0;
    }
    return 1;
}

bool checkNumber(string s)
{
    try{ 
        stoll(s);
    }
    catch (out_of_range& e){ 
        printl("Number too large!!!");
        return 0;
    }
    catch (invalid_argument& e){
        return 0;
    }
    return 1;
}

bool checkBinary(string ss)
{
    for (auto& e : ss) if (e!='1' && e!='0') return 0;
    try{ 
        stoll(ss, 0, 2);
    }
    catch (exception& e){ 
        return 0;
    }
    return 1;
}


string evaluate(vector<string> tokens)
{
    stack<string> values;
    stack<string> ops;
     
    for (int i = 0; i < tokens.size(); ++i)
    {
        if(tokens[i] == "(") 
            ops.push(tokens[i]);
        else if(checkNumber(tokens[i]))
            values.push(tokens[i]);
        else if(tokens[i] == ")")
        {
            while(!ops.empty() && ops.top() != "(")
            {
                string val2 = values.top(); values.pop();
                string val1 = values.top(); values.pop();
                values.push(compute(val1, val2, ops.top()));
                ops.pop();
            }
            if(!ops.empty()) ops.pop();
        }
        else
        {
            while(!ops.empty() && precedence(ops.top()) >= precedence(tokens[i]))
            {
                string val2 = values.top(); values.pop();
                string val1 = values.top(); values.pop();
                values.push(compute(val1, val2, ops.top()));
                ops.pop();
            }
            ops.push(tokens[i]);
        }
    }
    while(!ops.empty())
    {
        string val2 = values.top(); values.pop();
        string val1 = values.top(); values.pop();
        values.push(compute(val1, val2, ops.top()));
        ops.pop();
    }
    return values.top();
}