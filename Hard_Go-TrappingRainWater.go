//https://leetcode.com/problems/trapping-rain-water/

func trap(height []int) int {
    right := len(height) -1
    lv, rv := height[0], height[right]
    
    h := rv
    direction := lv < rv // true lr false rl
    if direction {
        h = lv
    }    
    sum,x := 0,0
        
    for left :=0; left < right -1; {
        if direction{
            left++
            lv = height[left]
            x = h - lv
        }else{
            right--
            rv = height[right]
            x = h - rv
        }
        if 0 <= x {
           sum += x        
        }else{
            direction = lv < rv       
            if direction {
                h = lv
            }else{
                h = rv
            }
        }     
    }    
    return sum
}
