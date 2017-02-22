---------------------
Assertion Add(@1471, Level 0):
(and (>= (Length h) 0)
     (>= (Length i) 0)
     (>= (Length (Concat h i)) 0)
     (= (Length (Concat h i)) (+ (Length h) (Length i))))
---------------------

---------------------
Assertion Add(@1471, Level 0):
(and (>= (Length j) 0)
     (>= (Length g) 0)
     (>= (Length (Concat j g)) 0)
     (= (Length (Concat j g)) (+ (Length j) (Length g))))
---------------------

---------------------
Assertion Add(@1251, Level 0):
(= (Length (AutomataDef teest)) 5)
---------------------

---------------------
Assertion Add(@1251, Level 0):
(= (Length (AutomataDef ee)) 2)
---------------------





=================================================================================
** cb_new_eq(): @0
(Concat h i)  = g




=================================================================================
** cb_new_eq(): @0
(Concat j g)  = w




=================================================================================
** cb_new_eq(): @0
w  = (AutomataDef teest)




=================================================================================
** cb_new_eq(): @0
(AutomataDef ee)  = h
