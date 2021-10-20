//https://leetcode.com/problems/4sum/
vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if(nums.size() < 4) return {};
        
        map<int,int> mnums;
        for(int x:nums) ++mnums[x];
        
        vector<int> vnums;
        vector<vector<int>> ans;
        for(auto fPtr: mnums){
            int x = fPtr.first, x2 = 2*x;
            if(fPtr.second >1){
                if(fPtr.second > 3)
                    if(x2 == target - x2) ans.push_back({x,x,x,x}); 
            
                if(fPtr.second > 2 && x2 !=target - x2 && target -x2 > x +(~(1<<30))){
                    if(mnums.find(target - 3*x) != mnums.end())
                     ans.push_back({x,x,x,target - 3*x});                               
                }
                vnums.push_back(x);
            }
            
            vnums.push_back(x);
        }
        mnums.clear();
        
        int n = vnums.size();
        int n_1 = n -1, n_2 = n_1-1;
        int z_val = vnums[n_1], y_val = target -vnums[n_2] - z_val;
        
        set<vector<int>> vans;
        for(int i = 0; i<n-3; ++i){
            int x1 = vnums[i];
            if(x1+ vnums[i+1] > target - vnums[i+2] - vnums[i+3])break;   
            if(x1+ vnums[n-3] < y_val)continue;   
            
            for(int j = i+1; j< n_2; ++j){
                int x2 = vnums[j];
                int t = x1+ x2;
                if(t > target - vnums[j+1] - vnums[j+2])break;
                if(t < y_val)continue;
                
                for(int k= j+1; k< n_1; ++k){
                    int x3 = vnums[k];
                    int t2 = target - x3 - t; 
                    if(vnums[k+1] > t2 )break;
                    if(z_val < t2)continue;
                
                    for(int l = k+1; l<n ; ++l)
                        if(vnums[l] == t2){
                           vans.insert({x1,x2, x3, vnums[l]});  
                            break;
                        }    
                }
            }
        }
        for(auto x:vans)ans.push_back(std::move(x));
        
        return ans;        
    }
