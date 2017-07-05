(declare-const s String)
(declare-const var String)
(declare-const ret String)


(assert (ite  (or (Contains s "<") (Contains s ">") ) 
              (= ret "x")
              (= ret s)
        ) 
)

(assert (= var (Concat "<scr" "ipt")) )

(assert (Contains s var) )

(assert (not (= ret "x") ) )

(check-sat)
(get-model)