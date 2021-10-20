//https://leetcode.com/problems/number-of-ways-to-separate-numbers/
//The best solution
constexpr int mod = 1e9 + 7;
constexpr int o = 1;

class Solution {
    using arr_2d = vector<vector<int>>; // typedef 
private:
    int m_n; // string length       
public:
                
    inline int dp_(const int x, const int y, arr_2d& lcp){
        if(x < 0) return 0;
        if(!x) return 1;
        return lcp[x - o][y];
    }
        
    int numberOfCombinations(string &num) {
        m_n = num.size();
		if(!m_n || num[0] == '0') return 0;
		if( m_n < 2) return m_n;
		   		
        const int n = m_n;
        // common largest prefix (below diagonal) 
        //and dp (diagonal & up of diagonal)
        
        
        
        arr_2d multimap(10,vector<int>());
        int last =0;
        
        for(int i = n-1; i >=0; --i){
            last = static_cast<int> (num[i] - '0');
            multimap[last].push_back(i);// desc sorted
        }
        
        if(last && multimap[last].size() ==n){
            if(n == 2) return n/2 +1;        
            //O(n) memory, fact: zero memory
            multimap[last].push_back(1);
            vector<int>prev(std::move(multimap[last])); 
            
            prev[0]=prev[1] =1;
            prev[3] =prev[2] =2;
            // upper slice of variants
            for(int j = 3; j <= n; ++j) prev[j] = 1 + (j>>1) + prev[j - 3];                  
            
            for(int inx=4; inx <= n; ++inx){
                for(int j = inx; j <= n; ++j) 
                    prev[j] = (prev[j] + prev[j - inx]) % mod;                  
             }
            return prev[n];
        }
        
        // O(n) .. O(n2) time 
        arr_2d clp(n - o, vector<int>(n));
        for (int i = n - 2; i >= 0; --i){
            vector<int>& list = multimap[static_cast<int> (num[i] - '0')];
                for(auto j: list){
                    if(i >= j) break;
                    clp[j - o][i] = j==n-1? 1 :clp[j + 1 - o][i + 1]+1;
                }
        }          
        multimap.clear();           
        
        
        // i= start of a being explored suffix, previous 'i' are already calculated values  
        for(int i = 1; i < n; ++i){ 
                           
            int i_ = i - o, i_dec = i - 1, j = i;
            
            // skip
            if(num[i]=='0') { for(; j< n; ++j)clp[i_][j] = dp_(i_dec, j,clp); continue; } 
                     
            int prev_diag{dp_(i_dec, i_dec, clp)};
            
            
            for(; j < (i<<1) && j <n; ++j){ // j = end of a being explored suffix, but not string                 
                                
                // thanks for https://leetcode.com/changoi/
                const int len = j-i+1, prev  = i-len, 
                lnLP = clp[i_][prev], 
                corr = (lnLP >= len || (num[prev + lnLP] < num[i + lnLP]))? 
                    dp_(prev-1, i_dec, clp): dp_(prev, i_dec, clp);
                
                clp[i_][j] = (dp_(i_dec,j, clp)+ prev_diag - corr ) % mod; 
            }
            if(j< m_n){
                int angul{(dp_(i_dec,j, clp)+ prev_diag) % mod}; //a bottom of the funnel of gathering values
                for( ;j< n; ++j)clp[i_][j] = angul;// padding to end of line
            }            
        }
        
        return dp_(n-1,n-1, clp);  
    }    
};
