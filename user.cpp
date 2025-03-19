#include <iostream>
#include <stack>
#include "polish.h"
#include "translate.h"

using namespace std;

// This code can handle input with or without spaces as long as the expressions are 
// formatted correctly with one-digit integers and valid operators.

int main() 
{
    string expression;

    string infix = "6*(5+(2+3)*8+3)";
    cout << "Infix: " << infix << endl;

    string postfix = translate(infix);
    cout << "Postfix: " << postfix << endl;

    int result = polish(postfix);
    cout << "Result: " << result << endl;
    cout << endl;
    cout << endl;

    cout << "Enter infix expressions: " << endl;

    while (getline(cin, expression))
    {
        if (expression.empty())
        {
            continue;
        }

        string postfix = translate(expression);
        int result = polish(postfix);

        cout << "Result: " << result << endl;
        cout << endl;
        cout << "Enter infix expressions: " << endl;
    }

    return 0;
}
