//https://leetcode.com/problems/reverse-nodes-in-k-group/
/**
 * Definition for singly-linked list.
 * class ListNode {
 *     val: number
 *     next: ListNode | null
 *     constructor(val?: number, next?: ListNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.next = (next===undefined ? null : next)
 *     }
 * }
 */

function reverseKGroup(head: ListNode | null, k: number): ListNode | null {
    if (k < 2 || head == null) return head;
    
    var arr_nodes:ListNode[] = new Array;
    var j : number;
    var x, y, endLastSegment :ListNode | null;
    
    for(x = head, j = 0; x != null; x = x.next){
        
        arr_nodes[j] = x; //push
        j++;
        
        if(j == k){
            arr_nodes[0].next = x.next; //must be on top, in the 'for' iteration the 'x' variable will be dirty node           
            j = 0;
            
            // head has just been = arr_nodes[0];           
            for(var i = 1; i< k ;i++) { 
                arr_nodes[i].next = arr_nodes[i - 1];
                y = arr_nodes[i];                    
            }  
            
            if(endLastSegment == null) head = y; else endLastSegment.next = y;                            
          
            x = endLastSegment = arr_nodes[0];       
            
        }// j ==k 
    }// for
    return head;
};
