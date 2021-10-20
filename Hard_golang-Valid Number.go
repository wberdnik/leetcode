//https://leetcode.com/problems/valid-number/
//Best time solition of Leetcode -0ms
const (
    START int32 =0    
    MANTICE int32 =1
    DOT int32 = 2 
    FRACTION int32 =3   
    SIGNDEGREE int32 = 4
    MANTICEDEGREE int32 = 5     
    MANTICEWAIT int32 =6
    MANTICEDEGREEWAIT int32 = 7
    DOTAFTERMANTICE int32 = 8
)


type Group struct{
    rules map[rune]int32
    endState bool
    digitState int32
}

type Diagram map[int32] Group

var diagram Diagram = Diagram{
    
    START: Group{
        endState : false,
        digitState: MANTICE,
        rules: map[rune]int32{
            '+': MANTICEWAIT,
            '-': MANTICEWAIT,
            '.': DOT,                
            },   
    },
   MANTICEWAIT: Group{
        endState : false,
        digitState: MANTICE,
        rules: map[rune]int32{                         
             '.': DOT,                                              
        },
    },
    
    MANTICE: Group{
        endState : true,
        digitState: MANTICE,
        rules: map[rune]int32{                          
            '.': DOTAFTERMANTICE,               
            'e': SIGNDEGREE,
            'E': SIGNDEGREE,
            }, 
    },    
    DOT: Group{
        endState : false,
        digitState: FRACTION,           
           
    },
    DOTAFTERMANTICE: Group{
        endState : true,
        digitState: FRACTION,
        rules: map[rune]int32{                          
            'e': SIGNDEGREE, 
            'E': SIGNDEGREE,
        },  
    },
    
    FRACTION: Group{
        endState : true,
        digitState: FRACTION,
        rules: map[rune]int32{            
            'e': SIGNDEGREE,
            'E': SIGNDEGREE,
            },
    },
    SIGNDEGREE: Group{
        endState : false,
        digitState: MANTICEDEGREE,
        rules: map[rune]int32{             
            '+': MANTICEDEGREEWAIT, 
            '-': MANTICEDEGREEWAIT, 
          },
    },
    
    MANTICEDEGREEWAIT: Group{
        endState : false,
        digitState: MANTICEDEGREE,                          
    },
    MANTICEDEGREE: Group{
        endState : true,
        digitState: MANTICEDEGREE,
    },
        
}

func isNumber(s string) bool { 
    
    state := START    
    for _, c := range s {
       
        group := diagram[state]
        if c <= '9' && c >= '0'{
            state = group.digitState
            continue
        }
        found := false
        for Runes,nextState := range group.rules { 
            if Runes == c {
                state = nextState
                found = true               
                break
            } 
        }

        if !found  {
            return false
        }   
    }    
    
    return diagram[state].endState
}

