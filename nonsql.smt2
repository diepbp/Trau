(declare-fun g () String) 
(declare-fun j () String)
(declare-fun w () String)   
(declare-fun t () String)   
(declare-fun p () String)  
(assert (RegexIn w (RegexStar (Str2Reg "abcdef")))) 
(assert (RegexIn w (RegexStar (Str2Reg "abcdefabcdef"))))
(assert (= w (Concat "abc" j)))
(assert (= j (Concat p "def")))
(assert (= g (Concat "def" w))) 
(assert (= t (Concat "ghi123" w)))
(check-sat)
(get-model)