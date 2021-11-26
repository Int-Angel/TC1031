#include <stack> 
using namespace std; 
class Solution {
public:
    bool isValid(string s) {
        stack<char> stack;
        if (s.size() <= 1) {
            return false;
        }
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '{' || s[i] == '(' || s[i] == '[') {
                stack.push(s[i]); 
                continue;
            } 
            else { 
                if (stack.empty())
                    return false;
                switch (s[i]) {
                    case '}':
                        if (stack.top() != '{')
                            return false;
                    break;
                        
                    case ')':
                        if (stack.top() != '(')
                            return false;
                    break;
                        
                    case ']':
                        if (stack.top() != '[')
                            return false;
                    break;
                    
                } 
                if (!stack.empty())
                    stack.pop();
            }     
        }
        return stack.empty();
    }
};
