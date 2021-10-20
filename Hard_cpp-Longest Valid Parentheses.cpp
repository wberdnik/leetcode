//https://leetcode.com/problems/longest-valid-parentheses/
 int longestValidParentheses(string s) {
        int n = s.length();
        
        int open =0;
        for(int i = n-1; i >=0; --i)
            if(s[i] == ')') ++open;
            else if(open)--open;
                else s[i] =0;
            
        open =0;
        int max_ph=0, curr_ph=0;
        
        for(char c :s){
            if(c){
                if(c==')'){
                   if(open){
                        ++curr_ph;
                        --open;
                       continue; 
                   }
                }else{
                    ++open;
                    continue;
                }    
            }
            if(curr_ph){
                max_ph = max(max_ph,curr_ph);
                curr_ph = 0;
            }
           
        }
        return max(max_ph,curr_ph)<<1;
