//https://leetcode.com/problems/longest-palindromic-substring/
class Solution {
private:
    int start{0};    
    int stop{0};
    int n;
    
    void register_res(int a, int b){
        if(stop -start < b - a){
            start = a;
            stop = b;
        }
    }
    
    void try_resize(int a, int b, string& s){
        
        while(true)
            if(s[a-1] == s[b+1]){
                if(a-1 == 0 || b+1 == n-1){
                   register_res(a-1, b+1);
                   return;
                }else{
                    --a;
                    ++b ;                               
                }
            }else{
                 register_res(a, b);
                 return;
            }
            
    }
    
public:
    string longestPalindrome(string s) {
        
         n = s.length();
        if(n < 2) return s;
        if(n == 2){
            if(s[0] == s[1]) return s;
            return {s[0]};
        }
        
        
        if(s[n-1] == s[n-2])register_res(n-2, n-1);
        if(s[0] == s[2])register_res(0, 2);
        if(s[0] == s[1]) register_res(0, 1);
        if(s[n-3] == s[n-1])register_res(n-3, n-1);       
        
        for(int i = 2; i <= n-2; ++i){
            if(s[i-1] == s[i+1]){
                try_resize(i-1, i+1, s);    
            }
            if(s[i-1] == s[i]){
                try_resize(i-1, i, s);
            }
        }
                
        return s.substr(start, stop - start +1);
    }
};
