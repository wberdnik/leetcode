//https://leetcode.com/problems/implement-strstr/
// Best time solution - 0ms
int strStr(string haystack, string needle) {
    
        int m  = needle.size();
        if(!m) return 0;
        int n = haystack.size();
        if(n < m) return ~0;
           
        vector <int> PI(m,0);
        int i,j;
        
        for(i =1, j =0; i < m; ++i){
            
            if(needle[i]==needle[j]){
                ++j;
                PI[i] = j;
            }else{
                if(j){ j = PI[j-1]; --i;}
                else PI[i] = 0;                    
            }
        }
        
        for(; i < m +n +1; ++i){
            if(i>m && haystack[i-m-1]==needle[j]){
                ++j;
                if(j==m) return i - (m<<1);
            }else{
                if(j){ j = PI[j-1]; --i;}                   
            }
        }
        
        
        return ~0;
    }
