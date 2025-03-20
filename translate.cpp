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

    if (op == '^')
    {
        return 3;
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

        // If current and next characters are operators, throw an error.
        if (i + 1 < n &&
            ((exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '%' || exp[i] == '^') &&
            (exp[i+1] == '+' || exp[i+1] == '-' || exp[i+1] == '*' || exp[i+1] == '/' || exp[i+1] == '%' || exp[i+1] == '^')))
        {
            if (exp[i] == '-' && exp[i+1] == '-') 
            {
                throw runtime_error("Error! Ambiguous consecutive '-' operators detected. Use parentheses to clarify.");
            }
            throw runtime_error("Error! Consecutive operators detected. Check your expression.");
        }

        // To detect negative numbers
        if (exp[i] == '-' && (i == 0 || exp[i-1] == '(' || exp[i-1] == '+' || exp[i-1] == '-' ||
                                        exp[i-1] == '*' || exp[i-1] == '/' || exp[i-1] == '%' || 
                                        exp[i-1] == '^')) 
            {
             if (i + 1 < n && isdigit(exp[i+1])) 
             {
                 result.push_back('-');
                 result.push_back(exp[i+1]);
                 i++; // Skip the digit that was just appended with a '-' sign
                 continue;
             }
             else {
                 throw runtime_error("Error! Invalid Negative Number Format.");
             }
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

            else 
            {
                throw runtime_error("Error! Mismatched parentheses.");
            }
        }

        else if ((exp[i] == '+') || (exp[i] == '-') || (exp[i] == '*') 
                || (exp[i] == '/') || (exp[i] == '%') || (exp[i] == '^'))
        {
            while (!s.empty() && precedence(s.top()) >= precedence(exp[i]))
            {
                result += s.top();
                s.pop();
            }

            s.push(exp[i]);
        }

        else{
            throw runtime_error("Error! Invalid Character in Expression.");
        }
    }

    while (!s.empty())
    {
        result += s.top();
        s.pop();
    }

    return result;
}