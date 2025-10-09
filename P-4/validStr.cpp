#include <iostream>
#include "P-2/Stack_Array.h"
using namespace std;

char opposite(char x){
    if(x==']') return '[';
    if(x=='}') return '{';
    if(x==')') return '(';
    return char();
}

bool isValid(const string S){

    Stack<char> refStack;
    for(char i:S){
        if(i=='[' || i=='{' || i=='('){
            refStack.push(i);
        }
        else if(i==')' || i==']' || i=='}'){
            if(refStack.isEmpty() || refStack.peek()!=opposite(i)) return false;
            refStack.pop();
        }
    }
    if(!refStack.isEmpty()) return false;
    return true;
}

int main(){
    string s1 = "({[]()})", s2 = "{[()]}", s3 = "({){}[])", s4 = "()[]{}", s5 = "(]", s6 = "([)]";
    cout<<isValid(s1)<<isValid(s2)<<isValid(s3)<<isValid(s4)<<isValid(s5)<<isValid(s6);
    return 0;
}