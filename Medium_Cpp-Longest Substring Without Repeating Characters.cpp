//https://leetcode.com/problems/longest-substring-without-repeating-characters/
int lengthOfLongestSubstring(string s) {
        
        int n = s.length();
        if(n < 2) return n;
        
        int max_len = 1;
        std::map<char,int> snake;
        
        for(int start =0, i =0; i < n; ++i){
            
            char c = s[i];
            start = max(start,snake[c]);                            
            max_len = max(max_len, i - start +1);
            if(n - start + 1 < max_len) break;
            snake[c] = i + 1;
        }
        return max_len;
    }
