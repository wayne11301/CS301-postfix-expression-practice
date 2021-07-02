
#include <exception>

#include <cmath>

#include <sstream>

#include "LinkedStack.h"

// Convert s to a double.

// If conversion fails, throw a logic_error exception.

double toDouble(const string& s) {

    istringstream in(s);

    double x;

    in >> x;

    if (!in) throw logic_error("Bad operand");

    return x;

}

double factorial(double x) {
    if (x <= 1) return 1;
    return factorial(x - 1) * x;
}

void updateTheStack(const string& tok, LinkedStack<double>& stk) {
    double temp1, temp2, result;

    if (tok == "+") {
        temp1 = stk.top();
        stk.pop();
        temp2 = stk.top();
        stk.pop();
        result = temp1 + temp2;
        stk.push(result);
    }
    else if (tok == "-") {
        temp1 = stk.top();
        stk.pop();
        temp2 = stk.top();
        stk.pop();
        result = temp2 - temp1;
        stk.push(result);
    }
    else if (tok == "*") {
        temp1 = stk.top();
        stk.pop();
        temp2 = stk.top();
        stk.pop();
        result = temp1 * temp2;
        stk.push(result);
    }
    else if (tok == "/") {
        temp1 = stk.top();
        stk.pop();
        temp2 = stk.top();
        if (temp1 == 0) throw range_error("Illegal operation");
        stk.pop();
        result = temp2 / temp1;
        stk.push(result);
    }
    else if (tok == "^") {
        temp1 = stk.top();
        stk.pop();
        temp2 = stk.top();
        stk.pop();
        result = pow(temp2, temp1);
        bool test1 = isinf(result);
        bool test2 = isnan(result);
        if (test1 || test2) throw range_error("Illegal operation");
        stk.push(result);
    }
    else if (tok == "!") {
        temp1 = stk.top();
        stk.pop();
        result = factorial(temp1);
        stk.push(result);
    }
    else if (tok == "~") {
        temp1 = stk.top();
        stk.pop();
        result = temp1 * -1;
        stk.push(result);
    }
    else {
        temp1 = toDouble(tok);
        stk.push(temp1);
    }
}

int main() {

    // 5 6 + means 5 + 6

    // 5 6 3 + * means 5 * (6 + 3)

    // 5 6 3 + * 2 ^ means (5 * (6 + 3)) ^ 2

    // Main should NOT be changed!

    string tok, exp;

    bool done = false;

    // read each line of input as a postfix expression and output the corresponding value

    do {

        cout << "Please type in a postfix expr or Enter to quit: ";

        getline(cin, exp);           // get next expression to process

        if (exp == "") done = true;  // user wants to quit

        else {

            try {

                istringstream in(exp);  // create a stringstream object

                LinkedStack<double> stk;      // create a stack of type double

                in >> tok;              // extract the first token from stream

                while (in)              // loop to process subsequent tokens

                {
                    updateTheStack(tok, stk);

                    in >> tok;          // get next token

                }

                double result = stk.top(); // this should be the final answer

                stk.pop();

                if (stk.isEmpty())

                    cout << exp << "  =  " << result << endl; // success!

                else
                    throw logic_error("Malformed expression"); // too many tokens on stack

            }

            catch (logic_error e) {

                cout << e.what() << endl;  // e.g. malformed expression, unsupported operator, not enough operands

            }

            catch (range_error e) {

                cout << "Range error: " << e.what() << endl;

            }

        }

    } while (!done);

    return 0;
}

