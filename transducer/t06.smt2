(declare-fun a () String)
(declare-fun b () String) 
(declare-fun c () String)
(declare-fun d () String) 

(assert (= a (ReplaceAll "eoffercode" "e" "1") )) 
(assert (= a "1off1rcod1") )
 

(check-sat)
(get-model)
