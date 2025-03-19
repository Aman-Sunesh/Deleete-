#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

// Function to evaluate a postfix expression
int polish(const string& expression) {
    stack<int> s;
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        // Check if token represents a number (also handles negative numbers)
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            s.push(stoi(token)); // Push operand to the stack
        } else {
            // Pop two operands from the stack
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            switch (token[0]) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
                case '%': s.push(a % b); break;
            }
        }
    }

    return s.top(); // Final result is on top of the stack
}

// Function to convert infix expression to postfix 
string translate(const string& infix) {
    stack<char> s;
    string postfix;
    int n = infix.size();

    for (int i = 0; i < n; i++) {
        char ch = infix[i];

        // Skip whitespace characters
        if (isspace(ch))
            continue;

        if (isdigit(ch)) {
            // Build a multi-digit number
            string num;
            while (i < n && isdigit(infix[i])) {
                num.push_back(infix[i]);
                i++;
            }
            i--; // Adjust for the extra increment in the loop
            postfix += num + " "; // Append the complete number and a space
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            // Pop operators until '(' is encountered
            while (!s.empty() && s.top() != '(') {
                postfix.push_back(s.top());
                postfix.push_back(' ');
                s.pop();
            }
            if (!s.empty()) {
                s.pop(); // Remove '('
            }
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
            // Precedence check:
            // For '+' and '-', pop all operators (except '(') because they have lower or equal precedence.
            // For '*' '/' '%', pop only operators of the same precedence.
            if (ch == '+' || ch == '-') {
                while (!s.empty() && s.top() != '(') {
                    postfix.push_back(s.top());
                    postfix.push_back(' ');
                    s.pop();
                }
            } else { // ch is '*' or '/' or '%'
                while (!s.empty() && (s.top() == '*' || s.top() == '/' || s.top() == '%')) {
                    postfix.push_back(s.top());
                    postfix.push_back(' ');
                    s.pop();
                }
            }
            s.push(ch); // Push the current operator
        }
    }

    // Pop any remaining operators from the stack
    while (!s.empty()) {
        postfix.push_back(s.top());
        postfix.push_back(' ');
        s.pop();
    }

    return postfix;
}

int main() {
    string expression;

    cout << "Enter infix expressions to translate and evaluate:\n";

    while (getline(cin, expression)) {
        if (expression.empty())
            continue;
            
        // Convert infix to postfix
        string postfix = translate(expression);

        // Display the postfix expression
        cout << "Postfix: " << postfix << endl;

        // Evaluate the postfix expression
        int result = polish(postfix);

        // Display the result
        cout << "Result: " << result << endl;
    }

    return 0;
}
