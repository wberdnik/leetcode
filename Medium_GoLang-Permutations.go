//https://leetcode.com/problems/permutations/

// So the theory of permutation, there are a value 'N' that a = pi1(pi2(...piN(a))) where pi - permutation 
// (pi1-piN - group of permutation)
// Let M - length of nums
// if M = 2 that N = 2 and pi is loop(involution) of permutation (1,2)
// if M = 3 that the loop of permutation is (3,2) with inner involution (1,2)
// example (1,2,3) -> (2,1,3) -> 
//         (2,3,1) -> (3,2,1) -> 
//         (3,1,2) -> (1,3,2) -> !!! (1,2,3)
//
// if M > 3 that we use symmetric group M-1 as inner loop
//
// for i = 0; i < M; i++ { 
//
//                      // example i =1,  nums = (1,4,3,2)  2 <=> 4
//
//    **** the inner loop of symmetric group M -1 as body ***
//                          // again  (1,4,3,2) 
//   if not first iteration { revert last (injection) transposition between current Am and group Am-1 }
//                          // initial (1,2,3,4)
//    that we have initial 'nums' and can take to inject in group Am-1
//      
//   if not last iteration {next transposition of Am and Am-1, example nums[M-1] <=> nums[M-1 - i -1]}
//                             // next injection (4,2,3,1)  4 <=> 1
//}

// push - to add a permutation to the answer
func push(ans [][]int, nums []int) [][]int{
    tmp := make([]int, len(nums))
    copy(tmp, nums)
	return append(ans,tmp)    
}

func permute(nums []int) (ans [][]int) {
	n := len(nums)
    
	if n<2 {
        ans = append(ans,nums)
		return
	}
        
    n6, n5, n4, n3 := 6, 5, 4, 3
    
    for a6 :=0; a6 < n6; a6++{
       for a5 :=0; a5 < n5; a5++{
            for a4 :=0; a4 < n4; a4++{
                for a3 :=0; a3 <n3; a3++{
                    ans = push(ans,nums)
                    nums[1], nums[0] = nums[0], nums[1]
                    ans = push(ans,nums)
                    
                    if n < n3 {
                        return
                    }
                    //Transpositions
                    nums[n3 -1], nums[1] = nums[1], nums[n3 -1]
                }//a3
                
                if n < n4 {
                    return
                }
    
                if a4 != 0{ //revert previous loop (so involution)
                    nums[n4 -1], nums[n4 -1 -a4] = nums[n4 - 1 -a4], nums[n4 - 1]
                }    
                if n4 -1  > a4 {
                    nums[n4 -1], nums[n4 -2 -a4] = nums[n4 -2 -a4], nums[n4 - 1]
                }
            }//a4   
            
            
            if n < n5 {
                return
            }
           
            if a5 != 0{ //revert previous loop (so involution)
                 nums[n5 -1], nums[n5 -1 -a5] = nums[n5 - 1 -a5], nums[n5 - 1]
            }    
            if n5 -1  > a5 {
                nums[n5 -1], nums[n5 -2 -a5] = nums[n5 -2 -a5], nums[n5 - 1]
            } 
            
        }//a5
        
        
        if n < n6 {
            return
        }
        if a6 != 0{ //revert previous loop (so involution)
             nums[n6 -1], nums[n6 -1 -a6] = nums[n6 - 1 -a6], nums[n6 - 1]
        }    
        if n6 -1  > a6 {
             nums[n6 -1], nums[n6 -2 -a6] = nums[n6 -2 -a6], nums[n6 - 1]
        }
    }//a6 
    
	return
}
