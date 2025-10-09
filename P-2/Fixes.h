//
// Created by Aayush Sharma on 21/08/25.
//
#pragma once

#include <iostream>
#include <string>
#include "Stack_Array.h"
using namespace std;

// Function to get the priority of an operator
inline int Priority(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

// Function to convert infix string to postfix string
inline string infix2postfix(string infix)
{
    Stack<char> operators;

    string pf{};

    for (int i=0;i<infix.length();i++)
    {
        if (infix[i] >= 'a' && infix[i] <= 'z' || infix[i] >= 'A' && infix[i] <= 'Z')
        {
            pf += infix[i];
        }

        else if (infix[i] == '(')
        {
            operators.push(infix[i]);
        }

        else if (infix[i] == ')')
        {
            while (operators.peek() != '(')
            {
                pf += operators.pop();
            }
            operators.pop();
        }

        else if (infix[i] == ' ') continue;

        else
        {
            if (!operators.isEmpty() && Priority(operators.peek()) >= Priority(infix[i]))
            {
                pf += operators.pop();
                operators.push(infix[i]);
            }
            else
            {
                operators.push(infix[i]);
            }
        }
    }
    while (!operators.isEmpty())
    {
        pf += operators.pop();
    }

    return pf;
}


std::string prefix2infix(std::string s)
{
    Stack<std::string> operands;
    int len = s.length();

    // Iterate through the string from right to left
    for (int i = len - 1; i >= 0; --i)
    {
        char currentChar = s[i];

        // If the character is an operand (letter)
        if (isalpha(currentChar)) // Check if it's an alphabet character
        {
            // Push the operand as a string onto the stack
            std::string temp(1, currentChar); // Efficient way to create a single-char string
            operands.push(temp);
        }
        // If the character is an operator
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '^')
        {
            // Check for sufficient operands to avoid underflow
            if (operands.size() < 2) {
                // You should throw an exception for an invalid expression
                return "Invalid Prefix Expression";
            }

            // Pop two operands from the stack
            std::string operand1 = operands.pop();
            std::string operand2 = operands.pop();

            // Construct the new infix expression with parentheses
            std::string newExpression = "(" + operand1 + currentChar + operand2 + ")";

            // Push the new expression back onto the stack
            operands.push(newExpression);
        }
        else if (currentChar != ' ')
        {
            // Handle other characters (e.g., spaces or invalid characters)
            return "Invalid character in expression";
        }
    }

    // The final result should be the single string left on the stack
    if (operands.size() == 1)
    {
        return operands.pop();
    }
    else {
        // This case handles expressions with too many operands (e.g., "AB+C")
        return "Invalid Prefix Expression";
    }
}


// conversion from infix to prefix
inline string infix2prefix(string infix)
{
    Stack<char> operators;

    string prefix{};

    for (int i=infix.length();i>=0;i--)
    {
        if (infix[i] >= 'a' && infix[i] <= 'z' || infix[i] >= 'A' && infix[i] <= 'Z')
        {
            prefix = infix[i] + prefix;
        }

        else if (infix[i] == ')')
        {
            operators.push(infix[i]);
        }

        else if (infix[i] == '(')
        {
            while (operators.peek() != ')')
            {
                prefix = operators.pop() + prefix;
            }
            operators.pop();
        }

        else if (infix[i] == ' ') continue;

        else
        {
            if (!operators.isEmpty() && Priority(operators.peek()) >= Priority(infix[i]))
            {
                prefix = operators.pop() + prefix;
                operators.push(infix[i]);
            }
            else
            {
                operators.push(infix[i]);
            }
        }
    }

    while (!operators.isEmpty())
    {
        prefix = operators.pop() + prefix;
    }

    return prefix;
}


bool isPal(string x)
{
    Stack<char> mystring;
    for (char c:x) mystring.push(c);
    int it=0;
    while (!mystring.isEmpty())
    {
        if (mystring.pop() != x[it])
        {
            return false;
        }
        it++;
    }
    return true;
}

string reverse(string x)
{
    Stack<char> mystring;
    for (char c:x) mystring.push(c);
    string reversed{};
    while (!mystring.isEmpty())
    {
        reversed += mystring.pop();
    }
    return reversed;
}
