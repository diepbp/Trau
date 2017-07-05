(declare-const v1 String)
(declare-const v2 String)
(declare-const v3 Int)
(declare-const ret String)



(assert (= v2 "<") )

(assert (ite (Contains v1 v2) 
             (and (= v3 (Indexof v1 v2)) (= ret (Substring v1 0 v3)) )
             (= ret v1)
        )
)



(check-sat)
(get-model)
