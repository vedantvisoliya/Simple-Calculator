#include "display.hpp"
#include <raylib.h>
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cctype>
#include <cmath>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <sstream>

using namespace std;

// ######### S T A R T  P A R S E R #########

// Function to check operator precedence
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

// Function to apply an operator to two operands
double applyOperator(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
            throw std::runtime_error("Division by zero");
        return a / b;
    case '^':
        return std::pow(a, b);
    default:
        throw std::runtime_error("Unknown operator");
    }
}

// Convert infix to postfix (RPN)
std::queue<std::string> infixToPostfix(const std::string &expression)
{
    std::stack<char> operators;
    std::queue<std::string> output;

    for (size_t i = 0; i < expression.length(); ++i)
    {
        char token = expression[i];

        if (std::isdigit(token) || token == '.')
        {
            // Handle numbers (multi-digit and floating point)
            std::string number;
            while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.'))
            {
                number += expression[i++];
            }
            --i; // Step back to process non-digit
            output.push(number);
        }
        else if (token == '(')
        {
            operators.push(token);
        }
        else if (token == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                output.push(std::string(1, operators.top()));
                operators.pop();
            }
            if (!operators.empty())
                operators.pop(); // Pop '('
        }
        else if (precedence(token) > 0)
        {
            // Handle operators
            while (!operators.empty() && precedence(operators.top()) >= precedence(token))
            {
                output.push(std::string(1, operators.top()));
                operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty())
    {
        output.push(std::string(1, operators.top()));
        operators.pop();
    }

    return output;
}

// Evaluate postfix (RPN) expression
double evaluatePostfix(std::queue<std::string> postfix)
{
    std::stack<double> operands;

    while (!postfix.empty())
    {
        std::string token = postfix.front();
        postfix.pop();

        if (std::isdigit(token[0]) || (token[0] == '.' && token.length() > 1))
        {
            operands.push(std::stod(token)); // Push numbers
        }
        else
        {
            // Apply operators
            if (operands.size() < 2)
                throw std::runtime_error("Invalid expression");
            double b = operands.top();
            operands.pop();
            double a = operands.top();
            operands.pop();
            operands.push(applyOperator(a, b, token[0]));
        }
    }

    if (operands.size() != 1)
        throw std::runtime_error("Invalid expression");
    return operands.top();
}

// ######### E N D  P A R S E R #########

// ######### REMOVING TRAILING ZEROES FORM DOUBLE VALUE ############

string removeTrailingZeros(double value) {
    ostringstream oss;
    oss << setprecision(15) << value; // Use high precision to capture all significant digits
    string str = oss.str();

    // Remove trailing zeros and possibly the decimal point if not needed
    size_t pos = str.find('.');
    if (pos != string::npos) {
        // Erase trailing zeros
        str.erase(str.find_last_not_of('0') + 1);
        // Erase the decimal point if it's the last character
        if (str.back() == '.') {
            str.pop_back();
        }
    }
    return str;
}
// ######### END OF THIS FUNCTION #############

void Display::draw(Color color){
    Rectangle rec = {30, 30, 500, 135};
    DrawRectangleRounded(rec, 0.2, 0, color);
}

void Display::display_output(){

    if (input == ""){
        DrawText(TextFormat("%i", 0), 40, 80, size, BLACK);
    }
    else {
        if (output == 0){
            display = input.c_str();
            DrawText(display, 40, 80, size, BLACK);
        }
    }
}

void Display::clear_display(){
    input = "";
    output = 0;
    error = "";
    display_key = 1;
}

void Display::result() {
    display_key = 0;
    try 
    {
        string expression = input;
        queue<string> postfix = infixToPostfix(expression);
        output = evaluatePostfix(postfix);
    }
    catch (const exception &e) 
    {
        error = e.what();
    }   
}

void Display::display_result() {
    const char* temp_output = (removeTrailingZeros(output)).c_str();
    if (error == ""){
        DrawText(temp_output, 40, 80, size, BLACK);
    }
    else {
        display = error.c_str();
        DrawText(display, 40, 80, size, BLACK);
    }
}