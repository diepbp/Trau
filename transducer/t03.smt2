(declare-fun a () String)
(declare-fun b () String) 

(assert (= a "eOffercode") ) 
(assert (= b (ToUpper a) ))  
 

(check-sat)
(get-model)
