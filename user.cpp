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

    // Predefined test cases
    string testCases[] = {
        "1 + 2 * 3 ^ 4",                                 // Expected: 163
        "-1 ^ 2 * 3 + 4 + 5 * 6 ^ 2",                    // Expected: 187
        "( 1 + 2 ) * ( 3 + 4 )",                         // Expected: 21
        "( ( ( 1 + 2 ) ) ) ^ ( ( ( 3 + ( 4 - 5 ) ) ) )", // Expected: 9
        "6*(5+(2+3)*8+3)"                                // Expected: 288
    };

    cout << "Running predefined test cases:" << endl << endl;
    cout << "-------------------------------------" << endl;
    
    for (const auto& infix : testCases) 
    {
        cout << "Infix: " << infix << endl;

        try 
        {
            string postfix = translate(infix);
            cout << "Postfix: " << postfix << endl;
            int result = polish(postfix);
            cout << "Result: " << result << endl;
        } 
        
        catch (const exception &e) 
        {
            cout << "Error: " << e.what() << endl;
        }

        cout << "-------------------------------------" << endl;
        cout << endl << endl;
    }


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
