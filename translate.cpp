#include <iostream>
#include <stack>
#include "translate.h"
#include "payload.h"

using namespace std;

int precedence(char op) 
{
    if (op == '+' || op == '-') 
    {
        return 1;
    }

    if (op == '*' || op == '/' || op == '%')
    {
        return 2;
    }

    return 0; 
}

string translate(const string& exp)
{
    stack<char> s;
    int n = exp.length();
    string result;

    for (int i = 0; i < n; i++)
    {
        if (isspace(exp[i])) 
        {
            continue;
        }

        if (isdigit(exp[i]))
        {
            result += exp[i];
        }

        else if (exp[i] == '(')
        {
            s.push(exp[i]);
        }

        else if (exp[i] == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                result += s.top();
                s.pop();
            }

            if (!s.empty() && s.top() == '(')
            {
                s.pop(); // We remove '(', but do not append it to the result
            }
        }

        else if ((exp[i] == '+') || (exp[i] == '-') || (exp[i] == '*') 
                || (exp[i] == '/') || (exp[i] == '%'))
        {
            while (!s.empty() && precedence(s.top()) >= precedence(exp[i]))
            {
                result += s.top();
                s.pop();
            }

            s.push(exp[i]);
        }
    }

    while (!s.empty())
    {
        result += s.top();
        s.pop();
    }

    return result;
}