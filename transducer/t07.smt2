(declare-fun a () String)
(declare-fun b () String) 
(declare-fun c () String)
(declare-fun d () String)
 
(assert (= a (Concat "eoffercod" b) )) 
(assert (= c (ReplaceAll a "e" "123") )) 
(assert (= c "123off123rcod123") )
(assert (= (Length b) 1)) 

(check-sat)
(get-model)
