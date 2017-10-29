(declare-fun s0 () String)
(declare-fun s1 () String)
(declare-fun s2 () String)
(declare-fun s3 () String)
(declare-fun s4 () String)
(declare-fun ret () String)



(assert (= s3 (Replace s2 "'"  "&quot;") ) )

(assert (= s4 (Replace s3 "<"  "&lt;") ) )

(assert (= ret (Replace s4 ">"  "&gt;") ) )


(assert (or (Contains ret "<") (Contains ret ">") ) )

(check-sat)
(get-model) 