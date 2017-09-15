(declare-fun x   () String)
(declare-fun x1  () String)
(declare-fun x2  () String)
(declare-fun x3  () String)

(declare-fun y   () String)
(declare-fun z   () String)
(declare-fun z1  () String)
(declare-fun z2  () String)
(declare-fun z3  () String)
(declare-fun w1  () String)
(declare-fun w2  () String)
(declare-fun w3  () String)
(declare-fun e1  () String)
(declare-fun cat () String) 

(assert (= cat "bxaaalertaaaaa")) 

(assert (= x (ReplaceAll cat "x" "yx")))

(assert (= x1 (ReplaceAll x "x" "aaquota")))

