(declare-fun a () String)
(declare-fun b () String) 

(assert (= a "eOfferCode") ) 
(assert (= b (ToUpper a) ))  

(check-sat)
(get-model)
