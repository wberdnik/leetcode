class Solution {
 
    CONST ALPHABET = ['A','B','c','D','E','F','G','H','I','J','K','L','M',
           'N','O','P','Q','R','S','T','U','V','W','X','Y','Z']; // could change
    CONST LENGTH_ANSWER = 5;
 
    public function convert($number){
        if($number < 1) return ''; //?? throw new Exception ??
        
        
        $a_size = count(self::ALPHABET);
        //O(1)
        $pow = pow(10, self::LENGTH_ANSWER-1);
        $ln_digits = self::LENGTH_ANSWER-1;
        $threshold =0;
        
        for(;$pow >= 1;   $pow /= 10, $ln_digits--){ 
            $step = $a_size * $pow;
            if($number < $threshold + $step){
                $ln_letters = self::LENGTH_ANSWER - $ln_digits;
                
                $zzz = str_repeat(self::ALPHABET[$a_size -1],$ln_letters -1);
                $letter = self::ALPHABET[floor(($number - $threshold)/$pow)];
                $digits = $ln_digits ? str_pad($number % $pow,$ln_digits,'0', STR_PAD_LEFT):'';
                
                return "$zzz$letter$digits";
                        
            }
            $threshold += $step;
        }
                
        return '';
    }
    public function testSolution($nums, $target) {
        $tests = [
          0 => '',
          18 => 'A0018',
          9999 => 'A9999',
          14656 => 'B4656',
          259999 => 'Z9999',
          265000 => 'ZF000',
          282510 => 'ZW510',
          283000 => 'ZX000',
          288824 => 'ZZZW4',
          288877 => 'ZZZZR',
          288885 => 'ZZZZZ',
          300000 => ''  
        ];
        foreach($tests as $in=>$out){
            if($this->convert($in) === $out){
                echo "$in - ok\n";
            }else{
                echo "$in - error ($out". "=>".$this->convert($in).")\n";
            }
        }
        
    }
}
