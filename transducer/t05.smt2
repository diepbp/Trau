(declare-fun a () String)
(declare-fun b () String) 
(declare-fun c () String)
(declare-fun d () String) 

(assert (= a "eOfferCode") ) 
(assert (= b (ToUpper a) ))  
(assert (= c (ToLower b) ))
(assert (= c "eoffercode" )) 
 

(check-sat)
(get-model)
