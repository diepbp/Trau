(declare-fun a () String)  
(declare-fun b () String)  
(declare-fun c () String)  
(declare-fun d () String)  
(declare-fun e () String)  
(declare-fun f () String)  

(assert (GrammarIn a (Str2Grm "$OREXPRESSION")))
(assert (= a (Concat "a" e)))
(assert (= b (Concat "abc" a)))
(assert (= c (Concat a "def"))) 

(assert (> (Length a) 30))

(check-sat)