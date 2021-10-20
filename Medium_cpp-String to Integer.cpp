//https://leetcode.com/problems/string-to-integer-atoi/
constexpr int limit = ~(1<<31); //max of positive
  int myAtoi(string s) {
        int state{0}; // 0 rest whitespaces, 1 - digits, 2 - sign complited, 3 - overflow
        int n = s.length();
        long ans =0;
        int pow;
        for(int i = n-1 ; i>=0; --i){
            
            if(isdigit(s[i])){
                switch(state){
                    case 2: [[throughfall]]
                    case 0: state = 1;pow = 1; ans = static_cast<int>(s[i] - '0');
                        break;
                    case 1: {
                           pow = limit/10 <= pow ? limit: pow *10;
                           int pie = static_cast<int>(s[i] - '0'); 
                           if(! pie) break;
                        
                           if( limit/pie <= pow || limit - pie * pow < ans){
                                ans = limit;
                                state =3;
                                break;
                            }                        
                            ans += pow *pie;
                                               }
                        break;
                }
                continue;
            }
            
            if(s[i] == '+' || s[i] =='-'){
                switch(state){
                    case 2:
                        state = 0;
                        pow = 1;
                        ans = 0;
                        break;
                    case 1:
                        state = 2;
                        if(s[i] =='-') ans = -ans;
                        break;
                    case 3:
                        state = 2;
                        if(s[i] =='-') ans = -limit -1;
                        break;
                }
                 
                continue;
            }
            if(s[i] == ' ' && state){
               state = 2; continue;
            }
            state = 0; pow = 1; ans = 0;
        }
        
        return ans;
    }
