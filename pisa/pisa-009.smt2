(declare-fun s () String)
(declare-fun ret0 () String)
(declare-fun ret1 () String)
(declare-fun ret2 () String)

(assert (= ret0 (Replace (Replace s "<"  "&lt;")  ">"  "&gt;") ) )

(assert (= ret1 (Concat ret0 "<br/>") ) )

(assert (or (Contains ret1 "<") (Contains ret1 ">") ) )


(check-sat)
(get-model)