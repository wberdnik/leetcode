// https://leetcode.com/problems/add-two-numbers/
//O(1) memory
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* r_l1 = new ListNode(0);
        ListNode* curr = r_l1;
        
        int cf {0};
        ListNode* i = l1;
        ListNode* j = l2;
        
        while(i!=nullptr || j != nullptr){                      
            int x = cf;
            if(i){
                x += i->val;
                i = i->next;
            }
             if(j){
                x += j->val;
                j = j->next;
            }
            cf = x / 10;       
            curr->next = new ListNode(x%10);
            curr = curr ->next;            
        }
        if(cf) curr->next = new ListNode(1);
         i =   r_l1 -> next;
            
        delete r_l1;
        return i;
    }
