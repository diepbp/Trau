(declare-fun s () String)
(declare-fun var () String)
(declare-fun ret () String)


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