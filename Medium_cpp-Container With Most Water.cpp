//https://leetcode.com/problems/container-with-most-water/
  int maxArea(vector<int>& height) {
        int n = height.size();
        
        vector<std::pair<int,int>> current;
        current.reserve(n-2);
                
        int bar = min(height[0], height[n-1]);        
                
        int mx = 0;
        for(int i =0; i< n; ++i){
            if(height[i] > bar){
                if(height[i] > mx)mx = height[i];
                current.push_back({i,height[i]});
            }
        }
        
        int volume = bar * (n-1);
        while(current.size() >1){
            auto start = current[0];
            auto stop = current[current.size() -1];
            
            
            bar = min(start.second, stop.second);
                        
            int new_volume = (stop.first - start.first) * bar;
            if(new_volume > volume){                
                volume = new_volume;
            }
            
            if((stop.first - start.first)*mx <= volume)break;
                    
            int j = 0;
            for(int i =0; i< current.size(); ++i){
                if(current[i].second > bar){
                    current[j]= current[i];
                    ++j;
               }
            }   
            current.resize(j);
        }
       return volume; 
    }
