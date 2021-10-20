//https://leetcode.com/problems/zigzag-conversion/
string convert(string s, int numRows) {
        int n = s.length();
        if(n <3 || numRows <2) return s;
        string ans(s);
        
        vector<int> blocks(numRows);
        int curr =0;
        int step = 2 * numRows -2;
        int tail = n % step;
        
        for(int i = 0;  ; ++i){
            blocks[i] = curr;
            if(i == numRows-1){
                break;
            }            
            if(!i){
                curr = n / step + (tail >0);
                continue;
            }
           curr += ((n /step)<<1) + (tail > i ) + ( tail > numRows && (numRows<<1) - tail   <= i + 1 );
        }
        
        int cur = 0;
        bool direction = false;
        for(char c: s){
            ans[blocks[cur]] = c;
            blocks[cur]++;
            direction? --cur : ++cur;            
            if(!cur || cur == numRows -1)direction = ! direction;                
        }
        
        return ans;
    }
