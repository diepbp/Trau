Input file: sat/small/1002.corecstrs.readable.smt2

260 creating /tmp/fat_str_convert/: OK
***********************************************
*              initGraph             *
-----------------------------------------------
 T_SELECT_1, PCTEMP_LHS_1,
(assert (= T_SELECT_1 (not (= PCTEMP_LHS_1 (- 1)))))

 T_SELECT_1, PCTEMP_LHS_1, I0_2, var_0xINPUT_15383, T0_2, T1_2, I0_2, T4_2, T0_2, T1_2, T2_2, T3_2, T2_2, T4_2, T5_2, T5_2, T4_2, PCTEMP_LHS_1, var_0xINPUT_15383, T0_2, T1_2, T0_2, T1_2,
(assert (ite T_SELECT_1 (and (= PCTEMP_LHS_1 (+ I0_2 0)) (= var_0xINPUT_15383 (Concat T0_2 T1_2)) (= I0_2 (Length T4_2)) (= 0 (Length T0_2)) (= T1_2 (Concat T2_2 T3_2)) (= T2_2 (Concat T4_2 T5_2)) (= T5_2 "GoogleAdServingTestC") (not (= T4_2 "GoogleAdServingTestC"))) (and (= PCTEMP_LHS_1 (- 1)) (= var_0xINPUT_15383 (Concat T0_2 T1_2)) (= 0 (Length T0_2)) (not (= T1_2 "GoogleAdServingTestC")))))

 T_2, PCTEMP_LHS_1,
(assert (= T_2 (not (= PCTEMP_LHS_1 (- 1)))))

 T_2,
(assert T_2)

 T_3, PCTEMP_LHS_1,
(assert (= T_3 (+ PCTEMP_LHS_1 20)))

 T_SELECT_2, PCTEMP_LHS_2,
(assert (= T_SELECT_2 (not (= PCTEMP_LHS_2 (- 1)))))

 T_SELECT_2, PCTEMP_LHS_2, I0_6, T_3, var_0xINPUT_15383, T0_6, T1_6, I0_6, T4_6, T_3, T0_6, T1_6, T2_6, T3_6, T2_6, T4_6, T5_6, T5_6, T4_6, PCTEMP_LHS_2, var_0xINPUT_15383, T0_6, T1_6, T_3, T0_6, T1_6,
(assert (ite T_SELECT_2 (and (= PCTEMP_LHS_2 (+ I0_6 T_3)) (= var_0xINPUT_15383 (Concat T0_6 T1_6)) (= I0_6 (Length T4_6)) (= T_3 (Length T0_6)) (= T1_6 (Concat T2_6 T3_6)) (= T2_6 (Concat T4_6 T5_6)) (= T5_6 "K") (not (= T4_6 "K"))) (and (= PCTEMP_LHS_2 (- 1)) (= var_0xINPUT_15383 (Concat T0_6 T1_6)) (= T_3 (Length T0_6)) (not (= T1_6 "K")))))

 T_5, PCTEMP_LHS_2,
(assert (= T_5 (= PCTEMP_LHS_2 (- 1))))

 T_6, T_5,
(assert (= T_6 (not T_5)))

 T_6,
(assert T_6)
(check-sat)

***********************************************
*              convertFile             *
-----------------------------------------------
242 creating /tmp/fat_str_convert/: OK
***********************************************
*              fat_theory                     *
-----------------------------------------------
String Input Var Set
***********************************************
var_0xINPUT_15383
T0_2
T1_2
T4_2
T2_2
T3_2
T5_2
T0_6
T1_6
T4_6
T2_6
T3_6
T5_6

***********************************************
Input loaded:
-----------------------------------------------
(let ((a!1 (= T_SELECT_1 (not (= PCTEMP_LHS_1 (- 1)))))
      (a!2 (ite T_SELECT_1
                (and (= PCTEMP_LHS_1 (+ I0_2 0))
                     (= var_0xINPUT_15383 (Concat T0_2 T1_2))
                     (= I0_2 (Length T4_2))
                     (= 0 (Length T0_2))
                     (= T1_2 (Concat T2_2 T3_2))
                     (= T2_2 (Concat T4_2 T5_2))
                     (= T5_2
                        __cOnStStR__x47_x6f_x6f_x67_x6c_x65_x41_x64_x53_x65_x72_x76_x69_x6e_x67_x54_x65_x73_x74_x43)
                     (not (= T4_2
                             __cOnStStR__x47_x6f_x6f_x67_x6c_x65_x41_x64_x53_x65_x72_x76_x69_x6e_x67_x54_x65_x73_x74_x43)))
                (and (= PCTEMP_LHS_1 (- 1))
                     (= var_0xINPUT_15383 (Concat T0_2 T1_2))
                     (= 0 (Length T0_2))
                     (not (= T1_2
                             __cOnStStR__x47_x6f_x6f_x67_x6c_x65_x41_x64_x53_x65_x72_x76_x69_x6e_x67_x54_x65_x73_x74_x43)))))
      (a!3 (= T_2 (not (= PCTEMP_LHS_1 (- 1)))))
      (a!4 (= T_SELECT_2 (not (= PCTEMP_LHS_2 (- 1)))))
      (a!5 (ite T_SELECT_2
                (and (= PCTEMP_LHS_2 (+ I0_6 T_3))
                     (= var_0xINPUT_15383 (Concat T0_6 T1_6))
                     (= I0_6 (Length T4_6))
                     (= T_3 (Length T0_6))
                     (= T1_6 (Concat T2_6 T3_6))
                     (= T2_6 (Concat T4_6 T5_6))
                     (= T5_6 __cOnStStR__x4b)
                     (not (= T4_6 __cOnStStR__x4b)))
                (and (= PCTEMP_LHS_2 (- 1))
                     (= var_0xINPUT_15383 (Concat T0_6 T1_6))
                     (= T_3 (Length T0_6))
                     (not (= T1_6 __cOnStStR__x4b))))))
  (and a!1
       a!2
       a!3
       T_2
       (= T_3 (+ PCTEMP_LHS_1 20))
       a!4
       a!5
       (= T_5 (= PCTEMP_LHS_2 (- 1)))
       (= T_6 (not T_5))
       T_6))
-----------------------------------------------


>> cb_reduce_app(): Concat(T0_2, T1_2)
>> cb_reduce_app(): Concat(T0_2, T1_2)
False update 
---------------------
Assertion Add(@1469, Level 0):
(and (>= (Length T0_2) 0)
     (>= (Length T1_2) 0)
     (>= (Length (Concat T0_2 T1_2)) 0)
     (= (Length (Concat T0_2 T1_2)) (+ (Length T0_2) (Length T1_2))))
---------------------


convert to: (Concat T0_2 T1_2)


>> cb_reduce_eq: var_0xINPUT_15383 = (Concat T0_2 T1_2)


 converted to : (and (>= (Length var_0xINPUT_15383) 0) (= var_0xINPUT_15383 (Concat T0_2 T1_2)))

>> cb_reduce_app(): Concat(T2_2, T3_2)
>> cb_reduce_app(): Concat(T2_2, T3_2)
False update 
---------------------
Assertion Add(@1469, Level 0):
(and (>= (Length T2_2) 0)
     (>= (Length T3_2) 0)
     (>= (Length (Concat T2_2 T3_2)) 0)
     (= (Length (Concat T2_2 T3_2)) (+ (Length T2_2) (Length T3_2))))
---------------------


convert to: (Concat T2_2 T3_2)


>> cb_reduce_eq: T1_2 = (Concat T2_2 T3_2)


 converted to : (and (>= (Length T1_2) 0) (= T1_2 (Concat T2_2 T3_2)))

>> cb_reduce_app(): Concat(T4_2, T5_2)
>> cb_reduce_app(): Concat(T4_2, T5_2)
False update 
---------------------
Assertion Add(@1469, Level 0):
(and (>= (Length T4_2) 0)
     (>= (Length T5_2) 0)
     (>= (Length (Concat T4_2 T5_2)) 0)
     (= (Length (Concat T4_2 T5_2)) (+ (Length T4_2) (Length T5_2))))
---------------------


convert to: (Concat T4_2 T5_2)


>> cb_reduce_eq: T2_2 = (Concat T4_2 T5_2)


 converted to : (and (>= (Length T2_2) 0) (= T2_2 (Concat T4_2 T5_2)))

>> cb_reduce_eq: T5_2 = __cOnStStR__x47_x6f_x6f_x67_x6c_x65_x41_x64_x53_x65_x72_x76_x69_x6e_x67_x54_x65_x73_x74_x43

---------------------
Assertion Add(@1249, Level 0):
(= (Length (AutomataDef GoogleAdServingTestC)) 20)
---------------------


 converted to : (and (>= (Length T5_2) 0)
     (>= (Length __cOnStStR__x47_x6f_x6f_x67_x6c_x65_x41_x64_x53_x65_x72_x76_x69_x6e_x67_x54_x65_x73_x74_x43)
         0)
     (=> (= T5_2 (AutomataDef GoogleAdServingTestC)) (= (Length T5_2) 20))
     (= T5_2 (AutomataDef GoogleAdServingTestC)))

>> cb_reduce_eq: T4_2 = __cOnStStR__x47_x6f_x6f_x67_x6c_x65_x41_x64_x53_x65_x72_x76_x69_x6e_x67_x54_x65_x73_x74_x43

---------------------
Assertion Add(@1249, Level 0):
(= (Length (AutomataDef GoogleAdServingTestC)) 20)
---------------------


 converted to : (and (>= (Length T4_2) 0)
     (>= (Length __cOnStStR__x47_x6f_x6f_x67_x6c_x65_x41_x64_x53_x65_x72_x76_x69_x6e_x67_x54_x65_x73_x74_x43)
         0)
     (=> (= T4_2 (AutomataDef GoogleAdServingTestC)) (= (Length T4_2) 20))
     (= T4_2 (AutomataDef GoogleAdServingTestC)))

>> cb_reduce_eq: T1_2 = __cOnStStR__x47_x6f_x6f_x67_x6c_x65_x41_x64_x53_x65_x72_x76_x69_x6e_x67_x54_x65_x73_x74_x43

---------------------
Assertion Add(@1249, Level 0):
(= (Length (AutomataDef GoogleAdServingTestC)) 20)
---------------------


 converted to : (and (>= (Length T1_2) 0)
     (>= (Length __cOnStStR__x47_x6f_x6f_x67_x6c_x65_x41_x64_x53_x65_x72_x76_x69_x6e_x67_x54_x65_x73_x74_x43)
         0)
     (=> (= T1_2 (AutomataDef GoogleAdServingTestC)) (= (Length T1_2) 20))
     (= T1_2 (AutomataDef GoogleAdServingTestC)))

>> cb_reduce_app(): Concat(T0_6, T1_6)
>> cb_reduce_app(): Concat(T0_6, T1_6)
False update 
---------------------
Assertion Add(@1469, Level 0):
(and (>= (Length T0_6) 0)
     (>= (Length T1_6) 0)
     (>= (Length (Concat T0_6 T1_6)) 0)
     (= (Length (Concat T0_6 T1_6)) (+ (Length T0_6) (Length T1_6))))
---------------------


convert to: (Concat T0_6 T1_6)


>> cb_reduce_eq: var_0xINPUT_15383 = (Concat T0_6 T1_6)


 converted to : (and (>= (Length var_0xINPUT_15383) 0) (= var_0xINPUT_15383 (Concat T0_6 T1_6)))

>> cb_reduce_app(): Concat(T2_6, T3_6)
>> cb_reduce_app(): Concat(T2_6, T3_6)
False update 
---------------------
Assertion Add(@1469, Level 0):
(and (>= (Length T2_6) 0)
     (>= (Length T3_6) 0)
     (>= (Length (Concat T2_6 T3_6)) 0)
     (= (Length (Concat T2_6 T3_6)) (+ (Length T2_6) (Length T3_6))))
---------------------


convert to: (Concat T2_6 T3_6)


>> cb_reduce_eq: T1_6 = (Concat T2_6 T3_6)


 converted to : (and (>= (Length T1_6) 0) (= T1_6 (Concat T2_6 T3_6)))

>> cb_reduce_app(): Concat(T4_6, T5_6)
>> cb_reduce_app(): Concat(T4_6, T5_6)
False update 
---------------------
Assertion Add(@1469, Level 0):
(and (>= (Length T4_6) 0)
     (>= (Length T5_6) 0)
     (>= (Length (Concat T4_6 T5_6)) 0)
     (= (Length (Concat T4_6 T5_6)) (+ (Length T4_6) (Length T5_6))))
---------------------


convert to: (Concat T4_6 T5_6)


>> cb_reduce_eq: T2_6 = (Concat T4_6 T5_6)


 converted to : (and (>= (Length T2_6) 0) (= T2_6 (Concat T4_6 T5_6)))

>> cb_reduce_eq: T5_6 = __cOnStStR__x4b

---------------------
Assertion Add(@1249, Level 0):
(= (Length (AutomataDef K)) 1)
---------------------


 converted to : (and (>= (Length T5_6) 0)
     (>= (Length __cOnStStR__x4b) 0)
     (=> (= T5_6 (AutomataDef K)) (= (Length T5_6) 1))
     (= T5_6 (AutomataDef K)))

>> cb_reduce_eq: T4_6 = __cOnStStR__x4b

---------------------
Assertion Add(@1249, Level 0):
(= (Length (AutomataDef K)) 1)
---------------------


 converted to : (and (>= (Length T4_6) 0)
     (>= (Length __cOnStStR__x4b) 0)
     (=> (= T4_6 (AutomataDef K)) (= (Length T4_6) 1))
     (= T4_6 (AutomataDef K)))

>> cb_reduce_eq: T1_6 = __cOnStStR__x4b

---------------------
Assertion Add(@1249, Level 0):
(= (Length (AutomataDef K)) 1)
---------------------


 converted to : (and (>= (Length T1_6) 0)
     (>= (Length __cOnStStR__x4b) 0)
     (=> (= T1_6 (AutomataDef K)) (= (Length T1_6) 1))
     (= T1_6 (AutomataDef K)))

>> cb_reduce_app(): Concat(T0_2, T1_2)
False update 

>> cb_reduce_app(): Concat(T2_2, T3_2)
False update 

>> cb_reduce_app(): Concat(T4_2, T5_2)
False update 

>> cb_reduce_app(): Concat(T0_6, T1_6)
False update 

>> cb_reduce_app(): Concat(T2_6, T3_6)
False update 

>> cb_reduce_app(): Concat(T4_6, T5_6)
False update 

>> cb_reduce_eq: var_0xINPUT_15383 = (Concat T0_2 T1_2)


>> cb_reduce_eq: T1_2 = (Concat T2_2 T3_2)


>> cb_reduce_eq: T2_2 = (Concat T4_2 T5_2)


>> cb_reduce_app(): Length( "GoogleAdServingTestC" ) = 20


>> cb_reduce_eq: T5_2 = (AutomataDef GoogleAdServingTestC)


>> cb_reduce_eq: T4_2 = (AutomataDef GoogleAdServingTestC)


>> cb_reduce_eq: T1_2 = (AutomataDef GoogleAdServingTestC)


>> cb_reduce_eq: var_0xINPUT_15383 = (Concat T0_6 T1_6)


>> cb_reduce_eq: T1_6 = (Concat T2_6 T3_6)


>> cb_reduce_eq: T2_6 = (Concat T4_6 T5_6)


>> cb_reduce_app(): Length( "K" ) = 1


>> cb_reduce_eq: T5_6 = (AutomataDef K)


>> cb_reduce_eq: T4_6 = (AutomataDef K)


>> cb_reduce_eq: T1_6 = (AutomataDef K)


>> cb_reduce_app(): Concat(T0_2, T1_2)
False update 

>> cb_reduce_app(): Concat(T2_2, T3_2)
False update 

>> cb_reduce_app(): Concat(T4_2, T5_2)
False update 

>> cb_reduce_app(): Concat(T0_6, T1_6)
False update 

>> cb_reduce_app(): Concat(T2_6, T3_6)
False update 

>> cb_reduce_app(): Concat(T4_6, T5_6)
False update 

>> cb_reduce_eq: var_0xINPUT_15383 = (Concat T0_2 T1_2)


>> cb_reduce_eq: T1_2 = (Concat T2_2 T3_2)


>> cb_reduce_eq: T2_2 = (Concat T4_2 T5_2)


>> cb_reduce_eq: T5_2 = (AutomataDef GoogleAdServingTestC)


>> cb_reduce_eq: T4_2 = (AutomataDef GoogleAdServingTestC)


>> cb_reduce_eq: T1_2 = (AutomataDef GoogleAdServingTestC)


>> cb_reduce_eq: var_0xINPUT_15383 = (Concat T0_6 T1_6)


>> cb_reduce_eq: T1_6 = (Concat T2_6 T3_6)


>> cb_reduce_eq: T2_6 = (Concat T4_6 T5_6)


>> cb_reduce_eq: T5_6 = (AutomataDef K)


>> cb_reduce_eq: T4_6 = (AutomataDef K)


>> cb_reduce_eq: T1_6 = (AutomataDef K)


>> cb_reduce_app(): Concat(T0_2, T1_2)
False update 

>> cb_reduce_app(): Concat(T2_2, T3_2)
False update 

>> cb_reduce_app(): Concat(T4_2, T5_2)
False update 

>> cb_reduce_app(): Concat(T0_6, T1_6)
False update 

>> cb_reduce_app(): Concat(T2_6, T3_6)
False update 

>> cb_reduce_app(): Concat(T4_6, T5_6)
False update 

>> cb_reduce_eq: var_0xINPUT_15383 = (Concat T0_2 T1_2)


>> cb_reduce_eq: T1_2 = (Concat T2_2 T3_2)


>> cb_reduce_eq: T2_2 = (Concat T4_2 T5_2)


>> cb_reduce_eq: T5_2 = (AutomataDef GoogleAdServingTestC)


>> cb_reduce_eq: T4_2 = (AutomataDef GoogleAdServingTestC)


>> cb_reduce_eq: T1_2 = (AutomataDef GoogleAdServingTestC)


>> cb_reduce_eq: var_0xINPUT_15383 = (Concat T0_6 T1_6)


>> cb_reduce_eq: T1_6 = (Concat T2_6 T3_6)


>> cb_reduce_eq: T2_6 = (Concat T4_6 T5_6)


>> cb_reduce_eq: T5_6 = (AutomataDef K)


>> cb_reduce_eq: T4_6 = (AutomataDef K)


>> cb_reduce_eq: T1_6 = (AutomataDef K)



Var In Length = {T0_2, T4_2, T0_6, T4_6, }
***********************************************
*               Starting Search               *
-----------------------------------------------
(let ((a!1 (+ (Length T0_2) (Length T1_2) (* (- 1) (Length (Concat T0_2 T1_2)))))
      (a!2 (+ (Length T2_2) (Length T3_2) (* (- 1) (Length (Concat T2_2 T3_2)))))
      (a!3 (+ (Length T4_2) (Length T5_2) (* (- 1) (Length (Concat T4_2 T5_2)))))
      (a!4 (+ (Length T0_6) (Length T1_6) (* (- 1) (Length (Concat T0_6 T1_6)))))
      (a!5 (+ (Length T2_6) (Length T3_6) (* (- 1) (Length (Concat T2_6 T3_6)))))
      (a!6 (+ (Length T4_6) (Length T5_6) (* (- 1) (Length (Concat T4_6 T5_6))))))
  (and (= a!1 0)
       (= a!2 0)
       (= a!3 0)
       (= (Length (AutomataDef GoogleAdServingTestC)) 20)
       (= a!4 0)
       (= a!5 0)
       (= a!6 0)
       (= (Length (AutomataDef K)) 1)
       (= (+ PCTEMP_LHS_1 (* (- 1) T_3)) (- 20))
       (>= (Length T0_2) 0)
       (>= (Length T1_2) 0)
       (>= (Length (Concat T0_2 T1_2)) 0)
       (>= (Length T2_2) 0)
       (>= (Length T3_2) 0)
       (>= (Length (Concat T2_2 T3_2)) 0)
       (>= (Length T4_2) 0)
       (>= (Length T5_2) 0)
       (>= (Length (Concat T4_2 T5_2)) 0)
       (>= (Length T0_6) 0)
       (>= (Length T1_6) 0)
       (>= (Length (Concat T0_6 T1_6)) 0)
       (>= (Length T2_6) 0)
       (>= (Length T3_6) 0)
       (>= (Length (Concat T2_6 T3_6)) 0)
       (>= (Length T4_6) 0)
       (>= (Length T5_6) 0)
       (>= (Length (Concat T4_6 T5_6)) 0)
       T_2
       T_6))




=================================================================================
** cb_new_eq(): @0
(AutomataDef GoogleAdServingTestC)  = T5_2
T5_2: length = 20 


** @2734 checkLengthConsistency

>> checkLengthConsistency: Passed

** @3443 Cross Check and Update: (AutomataDef GoogleAdServingTestC) == T5_2

>> @3263 Eval Intersection size = 2
>> @3309 at Number of elements: 1 
(AutomataDef GoogleAdServingTestC)


>> @3069 Eval Node (isIndependence = false): @0 (AutomataDef GoogleAdServingTestC)
532 at ../src/regex.cpp: Create Automaton of: known


>> @3332 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3347  Element 0: 
 Automaton known:
States: 
0 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 
Labels: 
65 67 71 83 84 100 101 103 105 108 110 111 114 115 116 118 
Transitions: 
	0--(71)--2
	2--(111)--3
	3--(111)--4
	4--(103)--5
	5--(108)--6
	6--(101)--7
	7--(65)--8
	8--(100)--9
	9--(83)--10
	10--(101)--11
	11--(114)--12
	12--(118)--13
	13--(105)--14
	14--(110)--15
	15--(103)--16
	16--(84)--17
	17--(101)--18
	18--(115)--19
	19--(116)--20
	20--(67)--21

Inits: 
0 
Accepts: 
21 

>> @3360 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 
Labels: 
65 67 71 83 84 100 101 103 105 108 110 111 114 115 116 118 
Transitions: 
	0--(71)--2
	2--(111)--3
	3--(111)--4
	4--(103)--5
	5--(108)--6
	6--(101)--7
	7--(65)--8
	8--(100)--9
	9--(83)--10
	10--(101)--11
	11--(114)--12
	12--(118)--13
	13--(105)--14
	14--(110)--15
	15--(103)--16
	16--(84)--17
	17--(101)--18
	18--(115)--19
	19--(116)--20
	20--(67)--21

Inits: 
0 
Accepts: 
21  @3452 at After all: 
Automaton known:
States: 
0 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 
Labels: 
65 67 71 83 84 100 101 103 105 108 110 111 114 115 116 118 
Inits: 
0 
Accepts: 
21 

>> @2908 update Equal Map
T5_2
(AutomataDef GoogleAdServingTestC)


** 2829 Propagate node: (AutomataDef GoogleAdServingTestC)
 parents_filtered 
(Concat T4_2 T5_2)



>> @2951 at __../src/StringTheory.cpp: Update Node: @0 (Concat T4_2 T5_2)

>> @3204 Eval Concat: T4_2 *concat* T5_2

>> @3069 Eval Node (isIndependence = false): @0 T4_2

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 
(Concat T4_2 T5_2)
>> @3013 at __../src/StringTheory.cpp: updated Concat value
 uNkNoWn




=================================================================================
** cb_new_eq(): @0
(Concat T4_2 T5_2)  = T2_2


** @2734 checkLengthConsistency

>> checkLengthConsistency: Passed

** @3443 Cross Check and Update: (Concat T4_2 T5_2) == T2_2

>> @3263 Eval Intersection size = 2
>> @3309 at Number of elements: 1 
(Concat T4_2 T5_2)


>> @3069 Eval Node (isIndependence = false): @0 (Concat T4_2 T5_2)

>> @3204 Eval Concat: T4_2 *concat* T5_2

>> @3069 Eval Node (isIndependence = false): @0 T4_2

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 

>> @3326 at __../src/StringTheory.cpp: UNKNOWN (1 elements)
@3452 at After all: 
uNkNoWn

>> @2908 update Equal Map
T2_2
(Concat T4_2 T5_2)


** 2829 Propagate node: (Concat T4_2 T5_2)
 parents_filtered 
(Concat T2_2 T3_2)



>> @2951 at __../src/StringTheory.cpp: Update Node: @0 (Concat T2_2 T3_2)

>> @3204 Eval Concat: T2_2 *concat* T3_2

>> @3069 Eval Node (isIndependence = false): @0 T2_2

>> @3263 Eval Intersection size = 2
>> @3309 at Number of elements: 1 
(Concat T4_2 T5_2)


>> @3069 Eval Node (isIndependence = false): @0 (Concat T4_2 T5_2)

>> @3204 Eval Concat: T4_2 *concat* T5_2

>> @3069 Eval Node (isIndependence = false): @0 T4_2

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 

>> @3326 at __../src/StringTheory.cpp: UNKNOWN (1 elements)

>> @3080 Value of variable: @0: uNkNoWn 
(Concat T2_2 T3_2)
>> @3013 at __../src/StringTheory.cpp: updated Concat value
 uNkNoWn




=================================================================================
** cb_new_eq(): @0
(Concat T2_2 T3_2)  = T1_2


** @2734 checkLengthConsistency

>> checkLengthConsistency: Passed

** @3443 Cross Check and Update: (Concat T2_2 T3_2) == T1_2

>> @3263 Eval Intersection size = 2
>> @3309 at Number of elements: 1 
(Concat T2_2 T3_2)


>> @3069 Eval Node (isIndependence = false): @0 (Concat T2_2 T3_2)

>> @3204 Eval Concat: T2_2 *concat* T3_2

>> @3069 Eval Node (isIndependence = false): @0 T2_2

>> @3263 Eval Intersection size = 2
>> @3309 at Number of elements: 1 
(Concat T4_2 T5_2)


>> @3069 Eval Node (isIndependence = false): @0 (Concat T4_2 T5_2)

>> @3204 Eval Concat: T4_2 *concat* T5_2

>> @3069 Eval Node (isIndependence = false): @0 T4_2

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 

>> @3326 at __../src/StringTheory.cpp: UNKNOWN (1 elements)

>> @3080 Value of variable: @0: uNkNoWn 

>> @3326 at __../src/StringTheory.cpp: UNKNOWN (1 elements)
@3452 at After all: 
uNkNoWn

>> @2908 update Equal Map
T1_2
(Concat T2_2 T3_2)


** 2829 Propagate node: (Concat T2_2 T3_2)
 parents_filtered 
(Concat T0_2 T1_2)



>> @2951 at __../src/StringTheory.cpp: Update Node: @0 (Concat T0_2 T1_2)

>> @3204 Eval Concat: T0_2 *concat* T1_2

>> @3069 Eval Node (isIndependence = false): @0 T0_2

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 
(Concat T0_2 T1_2)
>> @3013 at __../src/StringTheory.cpp: updated Concat value
 uNkNoWn




=================================================================================
** cb_new_eq(): @0
(Concat T0_2 T1_2)  = var_0xINPUT_15383


** @2734 checkLengthConsistency

>> checkLengthConsistency: Passed

** @3443 Cross Check and Update: (Concat T0_2 T1_2) == var_0xINPUT_15383

>> @3263 Eval Intersection size = 2
>> @3309 at Number of elements: 1 
(Concat T0_2 T1_2)


>> @3069 Eval Node (isIndependence = false): @0 (Concat T0_2 T1_2)

>> @3204 Eval Concat: T0_2 *concat* T1_2

>> @3069 Eval Node (isIndependence = false): @0 T0_2

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 

>> @3326 at __../src/StringTheory.cpp: UNKNOWN (1 elements)
@3452 at After all: 
uNkNoWn

>> @2908 update Equal Map
var_0xINPUT_15383
(Concat T0_2 T1_2)


** 2829 Propagate node: (Concat T0_2 T1_2)
 parents_filtered 





=================================================================================
** cb_new_eq(): @0
(AutomataDef K)  = T5_6
T5_6: length = 1 


** @2734 checkLengthConsistency

>> checkLengthConsistency: Passed

** @3443 Cross Check and Update: (AutomataDef K) == T5_6

>> @3263 Eval Intersection size = 2
>> @3309 at Number of elements: 1 
(AutomataDef K)


>> @3069 Eval Node (isIndependence = false): @0 (AutomataDef K)
532 at ../src/regex.cpp: Create Automaton of: known


>> @3332 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3347  Element 0: 
 Automaton known:
States: 
0 1 
Labels: 
75 
Transitions: 
	0--(75)--1

Inits: 
0 
Accepts: 
1 

>> @3360 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 
Labels: 
75 
Transitions: 
	0--(75)--1

Inits: 
0 
Accepts: 
1  @3452 at After all: 
Automaton known:
States: 
0 1 
Labels: 
75 
Inits: 
0 
Accepts: 
1 

>> @2908 update Equal Map
T5_6
(AutomataDef K)


** 2829 Propagate node: (AutomataDef K)
 parents_filtered 
(Concat T4_6 T5_6)



>> @2951 at __../src/StringTheory.cpp: Update Node: @0 (Concat T4_6 T5_6)

>> @3204 Eval Concat: T4_6 *concat* T5_6

>> @3069 Eval Node (isIndependence = false): @0 T4_6

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 
(Concat T4_6 T5_6)
>> @3013 at __../src/StringTheory.cpp: updated Concat value
 uNkNoWn




=================================================================================
** cb_new_eq(): @0
(Concat T4_6 T5_6)  = T2_6


** @2734 checkLengthConsistency

>> checkLengthConsistency: Passed

** @3443 Cross Check and Update: (Concat T4_6 T5_6) == T2_6

>> @3263 Eval Intersection size = 2
>> @3309 at Number of elements: 1 
(Concat T4_6 T5_6)


>> @3069 Eval Node (isIndependence = false): @0 (Concat T4_6 T5_6)

>> @3204 Eval Concat: T4_6 *concat* T5_6

>> @3069 Eval Node (isIndependence = false): @0 T4_6

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 

>> @3326 at __../src/StringTheory.cpp: UNKNOWN (1 elements)
@3452 at After all: 
uNkNoWn

>> @2908 update Equal Map
T2_6
(Concat T4_6 T5_6)


** 2829 Propagate node: (Concat T4_6 T5_6)
 parents_filtered 
(Concat T2_6 T3_6)



>> @2951 at __../src/StringTheory.cpp: Update Node: @0 (Concat T2_6 T3_6)

>> @3204 Eval Concat: T2_6 *concat* T3_6

>> @3069 Eval Node (isIndependence = false): @0 T2_6

>> @3263 Eval Intersection size = 2
>> @3309 at Number of elements: 1 
(Concat T4_6 T5_6)


>> @3069 Eval Node (isIndependence = false): @0 (Concat T4_6 T5_6)

>> @3204 Eval Concat: T4_6 *concat* T5_6

>> @3069 Eval Node (isIndependence = false): @0 T4_6

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 

>> @3326 at __../src/StringTheory.cpp: UNKNOWN (1 elements)

>> @3080 Value of variable: @0: uNkNoWn 
(Concat T2_6 T3_6)
>> @3013 at __../src/StringTheory.cpp: updated Concat value
 uNkNoWn




=================================================================================
** cb_new_eq(): @0
(Concat T2_6 T3_6)  = T1_6


** @2734 checkLengthConsistency

>> checkLengthConsistency: Passed

** @3443 Cross Check and Update: (Concat T2_6 T3_6) == T1_6

>> @3263 Eval Intersection size = 2
>> @3309 at Number of elements: 1 
(Concat T2_6 T3_6)


>> @3069 Eval Node (isIndependence = false): @0 (Concat T2_6 T3_6)

>> @3204 Eval Concat: T2_6 *concat* T3_6

>> @3069 Eval Node (isIndependence = false): @0 T2_6

>> @3263 Eval Intersection size = 2
>> @3309 at Number of elements: 1 
(Concat T4_6 T5_6)


>> @3069 Eval Node (isIndependence = false): @0 (Concat T4_6 T5_6)

>> @3204 Eval Concat: T4_6 *concat* T5_6

>> @3069 Eval Node (isIndependence = false): @0 T4_6

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 

>> @3326 at __../src/StringTheory.cpp: UNKNOWN (1 elements)

>> @3080 Value of variable: @0: uNkNoWn 

>> @3326 at __../src/StringTheory.cpp: UNKNOWN (1 elements)
@3452 at After all: 
uNkNoWn

>> @2908 update Equal Map
T1_6
(Concat T2_6 T3_6)


** 2829 Propagate node: (Concat T2_6 T3_6)
 parents_filtered 
(Concat T0_6 T1_6)



>> @2951 at __../src/StringTheory.cpp: Update Node: @0 (Concat T0_6 T1_6)

>> @3204 Eval Concat: T0_6 *concat* T1_6

>> @3069 Eval Node (isIndependence = false): @0 T0_6

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 
(Concat T0_6 T1_6)
>> @3013 at __../src/StringTheory.cpp: updated Concat value
 uNkNoWn




=================================================================================
** cb_new_eq(): @0
var_0xINPUT_15383  = (Concat T0_6 T1_6)


** @2734 checkLengthConsistency

>> checkLengthConsistency: Passed

** @3443 Cross Check and Update: var_0xINPUT_15383 == (Concat T0_6 T1_6)

>> @3263 Eval Intersection size = 3
>> @3309 at Number of elements: 2 
(Concat T0_2 T1_2)
(Concat T0_6 T1_6)


>> @3069 Eval Node (isIndependence = false): @0 (Concat T0_2 T1_2)

>> @3204 Eval Concat: T0_2 *concat* T1_2

>> @3069 Eval Node (isIndependence = false): @0 T0_2

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 

>> @3069 Eval Node (isIndependence = false): @0 (Concat T0_6 T1_6)

>> @3204 Eval Concat: T0_6 *concat* T1_6

>> @3069 Eval Node (isIndependence = false): @0 T0_6

>> @3263 Eval Intersection size = 1
>> @3309 at Number of elements: 0 


>> @3326 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3080 Value of variable: @0: uNkNoWn 

>> @3326 at __../src/StringTheory.cpp: UNKNOWN (2 elements)
@3452 at After all: 
uNkNoWn

>> @2908 update Equal Map
(Concat T0_6 T1_6)
var_0xINPUT_15383
(Concat T0_2 T1_2)


** 2829 Propagate node: var_0xINPUT_15383
 parents_filtered 


*******************************************
[PUSH]: Level = 1

*******************************************

*******************************************
[PUSH]: Level = 2

*******************************************

*******************************************
[POP]: Level = 1

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap
New disequality: T4_6 != (AutomataDef K)

*******************************************
[PUSH]: Level = 2

*******************************************

*******************************************
[POP]: Level = 1

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[POP]: Level = 0

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[PUSH]: Level = 1

*******************************************

*******************************************
[PUSH]: Level = 2

*******************************************
New disequality: T4_6 != (AutomataDef K)

*******************************************
[PUSH]: Level = 3

*******************************************

*******************************************
[PUSH]: Level = 4

*******************************************

*******************************************
[PUSH]: Level = 5

*******************************************

*******************************************
[POP]: Level = 4

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[POP]: Level = 3

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[POP]: Level = 2

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[POP]: Level = 1

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[POP]: Level = 0

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap
New disequality: T4_2 != (AutomataDef GoogleAdServingTestC)

*******************************************
[PUSH]: Level = 1

*******************************************

*******************************************
[PUSH]: Level = 2

*******************************************

*******************************************
[PUSH]: Level = 3

*******************************************
New disequality: T4_6 != (AutomataDef K)

*******************************************
[PUSH]: Level = 4

*******************************************

*******************************************
[PUSH]: Level = 5

*******************************************

*******************************************
[PUSH]: Level = 6

*******************************************

*******************************************
[PUSH]: Level = 7

*******************************************

*******************************************
[POP]: Level = 6

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[POP]: Level = 5

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[POP]: Level = 4

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[POP]: Level = 3

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[POP]: Level = 2

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[POP]: Level = 1

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[POP]: Level = 0

*******************************************
Remove in internalVarMap
Remove in equalMap
Remove in length_LanguageMap

*******************************************
[PUSH]: Level = 1

*******************************************

*******************************************
[PUSH]: Level = 2

*******************************************

*******************************************
[PUSH]: Level = 3

*******************************************
New disequality: T4_6 != (AutomataDef K)

*******************************************
[PUSH]: Level = 4

*******************************************

*******************************************
[PUSH]: Level = 5

*******************************************

*******************************************
[PUSH]: Level = 6

*******************************************



vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                cb_final_check @ Level [6] 
=============================================================
Connected Variables

4019 var_0xINPUT_15383 = :
Start 

T0_6
T4_6
(AutomataDef K)
T3_6

Start 

T0_2
T4_2
(AutomataDef GoogleAdServingTestC)
T3_2


** Reset():

** Delete()
