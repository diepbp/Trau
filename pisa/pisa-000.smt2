(declare-fun v1 () String)
(declare-fun v2 () String)
(declare-fun v3 () Int)
(declare-fun ret () String)



(assert (= v2 "a") )

(assert (ite (Contains v1 v2) 
             (and (= v3 (Indexof v1 v2)) (= ret (Substring v1 0 v3)) )
             (= ret "123")
        )
)

(assert (or (Contains ret "b") (Contains ret "a") ) )

(check-sat)
(get-model)
