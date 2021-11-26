#include <string>
using namespace std;

class Solution {
public:
    int reverse(int x) {
        string str = ""; 
        str += to_string(x);
        string str2 = "";
        
        if(x < 0){
            str2 += "-";
        }
        
        for(int i = str.length()-1; i >= 0; i--){
            if(str[i] == '-'){
                continue;
            }else{
                str2 += str[i]; 
            }
        }
        
        try{
            return stoi(str2);
        }catch(exception e){
            return 0;
        }
    }
};