//https://leetcode.com/problems/merge-k-sorted-lists/
// The best time solution of leetcode

 public ListNode mergeKLists(ListNode[] lists) {
        int n;
               
        for(n = lists.length; n > 1 && lists[n-1] == null; n--);
               
        for(int i = 0; i<n; i++){
            if(lists[i] == null){
                n--;
                lists[i] = lists[n];                
            }
        }
                
        if(n == 0){
            return null;
        }
        
        for(n = n-1; n >0; ){
           for(int lValue =0 ;lValue < n; lValue++, n--){
                if(lists[n] != null){                   
                   
                    int rValue = n;
                    ListNode  lP = lists[lValue], x, rP =lists[rValue];                
                    boolean first = true;
                    while(rP.val <= lists[lValue].val){
                        x = rP.next;
                        if(first){
                            lP = rP;  
                            first = false;
                        } 
                        rP.next = lists[lValue];
                        lists[lValue] = rP; // remove first from R to L
                        lists[rValue] = x; // move first R-value
                        rP =x;
                        if(rP == null){
                            break;
                        }
                    }
                    if(rP == null) continue;                    
                                   
                   
                    while(lP.next != null && rP != null){
                        if(rP.val <= lP.next.val){
               
                            x = rP.next;
           
                            rP.next = lP.next;
                            lP.next = rP; // remove first from R to L
                            
                            lists[rValue] = x; // move first R-value
                            rP = x;
                        }else{
                            lP = lP.next;
                        }
                    }   
                       
                    for(;lP.next != null;lP = lP.next);
                    lP.next = rP; 
                   
                }                
           }        
        }
        
        return lists[0];
    }
   
