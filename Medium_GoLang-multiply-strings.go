//https://leetcode.com/problems/multiply-strings/
func multiply(num1 string, num2 string) string {
    if num1 == "0" || num2 == "0"{
        return "0"
    }
    n, m := len(num1), len(num2)
    k := n+m
    product := make([]byte, k)
    for i:=0; i<n; i++{
        f := (num1[n - i -1] - '0')
        for j:=0; j<m; j++{ 
            kij := k-i-j
            sum := uint16(f * (num2[m - j -1] -'0') + product[kij -1])
            product[kij -1] = byte(sum%10) 
            if sum/10 > 0 {
               sum =  sum/10 + uint16(product[kij - 2])
               product[kij -2] = byte(sum%10)
               if sum/10 > 0 {
                   product[kij -3] +=  byte(sum/10)                 
               }
            }
            
        }
    }
   
    for i, sum := range product{ 
        product[i] = sum + '0'         
    }
    if product[0] == '0'{
      return string(product[1:])  
    }
    return string(product)
}
