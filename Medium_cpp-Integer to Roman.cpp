//https://leetcode.com/problems/integer-to-roman/
class Solution {
     std::map<int,string> base{
            {1,"I"},{4,"IV"},{5,"V"},{9,"IX"},
            {10,"X"},{40,"XL"},{50,"L"},{90,"XC"}, 
            {100,"C"},{400,"CD"},{500,"D"}, {900,"CM"},
            {1000,"M"},
        };
    
void repeatStr(int n, const string patt, string& ans){
    while(n--) ans+=patt;
}
public:
    string intToRoman(int num) {
        if(num == 0)return "";
        if(num == 1)return "I";
        
        string ans;
        
        int devider = 1000;
        while(num){
            int probe = num/devider;
            if(probe){
                switch(probe){
                    case 1:     
                        [[fallthrough]];
                    case 2: 
                        [[fallthrough]];
                    case 3: repeatStr(probe, base[devider],ans); break;
                        
                    case 4:  
                        [[fallthrough]];    
                    case 5:  
                        ans+=base[probe*devider];break;        
                    
                        
                    case 6: 
                        [[fallthrough]];
                    case 7: 
                        [[fallthrough]];
                    case 8: ans += base[5*devider];
                         repeatStr(probe -5, base[devider],ans);
                        
                    case 9:  ans+=base[probe*devider];break;      
                }
                
            }
            num %= devider;
            devider /= 10;
        }
        
        return ans;
    }
};
