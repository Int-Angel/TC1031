#include <string>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if(x <0){
            return false;
        }
        
        string str = ""; 
        str += to_string(x);
        string str2 = "";
        
        for(int i = str.length()-1; i >= 0; i--){
            if(str[i] == '-'){
                continue;
            }else{
                str2 += str[i]; 
            }
        }
        
        return str.compare(str2) == 0;
        
    }
};
