// C++ program to check for balanced brackets.
#include <bits/stdc++.h>
using namespace std;

// Function to check if brackets are balanced
bool ispar(const string& s) {  // Pass string by reference
  
    // Declare a stack to hold the previous brackets.
    stack<char> stk;
    for (int i = 0; i < s.length(); i++) {
        
        // Check if the character is an opening bracket
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stk.push(s[i]); 
        } 
      
        else {
            // If it's a closing bracket, check if the stack is non-empty
            // and if the top of the stack is a matching opening bracket
            if (!stk.empty() && 
                ((stk.top() == '(' && s[i] == ')') ||
                 (stk.top() == '{' && s[i] == '}') ||
                 (stk.top() == '[' && s[i] == ']'))) {
                stk.pop(); // Pop the matching opening bracket
            }
            else {
                return false; // Unmatched closing bracket
            }
        }
    }
    
    // If stack is empty, return true (balanced), otherwise false
    return stk.empty();
}

int main() {
  
    string s = "{()}[]";

    // Function call
    if (ispar(s))
        cout << "true";
    else
        cout << "false";
    return 0;
}
