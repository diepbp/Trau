(declare-fun a () String)
(declare-fun b () String) 

(assert (= a "eOfferCode") ) 
(assert (= b (ToLower a) )) 
(assert (= b "eoffercode") )
 

(check-sat)
(get-model)
