(declare-const s String)
(declare-const ret String)


(assert (ite  (or (Contains s "<") (Contains s ">") ) 
              (= ret "x")
              (= ret s)
        ) 
)

(assert (Contains s "sc") )

(assert (Contains s "ript scr=") )

(assert (not (= ret "x") ) )

(check-sat)
(get-model)